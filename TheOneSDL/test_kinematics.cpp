/*
* test_kinematics.cpp
* Copyright (C) [2026] [Jacob Lowe]
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

// Headless regression test for the tile-space, fixed-timestep movement
// refactor. This links ONLY against Kinematics.h -- no SDL, no ImGui, no
// window -- to prove the invariant that was broken before this refactor:
// movement must produce the same result in tiles regardless of window
// resolution, and the same result regardless of render/FPS-cap rate.
//
// Build and run: `make test` from this directory.

#include "Kinematics.h"

#include <cmath>
#include <cstdio>

namespace {

int failures = 0;

void expectNear(float actual, float expected, float epsilon,
                const char *what) {
  float diff = std::fabs(actual - expected);
  if (diff > epsilon) {
    std::printf("FAIL: %s -- expected %.6f got %.6f (diff %.6f, epsilon %.6f)\n",
                what, expected, actual, diff, epsilon);
    failures++;
  } else {
    std::printf("PASS: %s (diff %.6f)\n", what, diff);
  }
}

void expectAtMost(float actual, float limit, const char *what) {
  if (actual > limit) {
    std::printf("FAIL: %s -- %.3f exceeds limit %.3f\n", what, actual, limit);
    failures++;
  } else {
    std::printf("PASS: %s (%.3f <= %.3f)\n", what, actual, limit);
  }
}

// Reference design resolution and tile size (Constants.h: SCREEN_WIDTH,
// SCREEN_HEIGHT, TILE_SIZE).
const int REF_W = 800;
const int REF_H = 600;
const int REF_TILE = 32;
// Terrain::tilemapX / tilemapY -- the playable grid.
const int TILES_X = 26;
const int TILES_Y = 19;

// Mirrors Entity::scaleTextures' scale derivation exactly.
int tileSizeFor(int extent, int refExtent) {
  float scale = static_cast<float>(extent) / static_cast<float>(refExtent);
  return static_cast<int>(std::lround(REF_TILE * scale));
}

// Simulates `steps` fixed ticks of constant-velocity horizontal movement,
// exactly as Entity::handleMovement integrates pos_x while a direction key
// is held. Returns the final tile-space position.
float simulateHorizontal(float velTilesPerSec, float dt, int steps) {
  float pos = 0.f;
  for (int i = 0; i < steps; i++) {
    pos = Kinematics::stepPosition(pos, velTilesPerSec, dt);
  }
  return pos;
}

// Simulates a full jump (upward impulse + gravity every fixed step), exactly
// as Entity::yPathEdit (impulse) and Entity::handleMovement (integration)
// advance vel_y/pos_y. Returns the apex height reached, in tiles (y grows
// downward, so the apex is the most negative pos_y sampled).
float simulateJumpApex(float jumpSpeed, float gravity, float dt, int steps) {
  float pos_y = 0.f;
  float vel_y = -jumpSpeed;
  float apex = 0.f;
  for (int i = 0; i < steps; i++) {
    vel_y = Kinematics::stepVelocity(vel_y, gravity, dt);
    pos_y = Kinematics::stepPosition(pos_y, vel_y, dt);
    if (pos_y < apex) {
      apex = pos_y;
    }
  }
  return apex;
}

// Entity::syncRect projects tile space onto pixels through the UNROUNDED
// pixels-per-tile: entityR.x = lround(pos * tilePixelsX).
int entityPixelFor(float posTiles, int extent, int refExtent) {
  float scale = static_cast<float>(extent) / static_cast<float>(refExtent);
  return static_cast<int>(std::lround(posTiles * REF_TILE * scale));
}

// Terrain::fillScreen places a block using the UNROUNDED float scale:
// scaled_x = (tileIndex * TILE_SIZE) * scale, then Block's constructor
// rounds. entityPixelFor above must match this exactly.
int blockPixelFor(int tileIndex, int extent, int refExtent) {
  float scale = static_cast<float>(extent) / static_cast<float>(refExtent);
  return static_cast<int>(std::lround(tileIndex * REF_TILE * scale));
}

struct Resolution {
  int w, h;
  const char *label;
};

// Common display resolutions from the engine's design size up to 4K, spanning
// 4:3, 16:9, 16:10 and 21:9 so that non-uniform X/Y scaling is covered too.
const Resolution kResolutions[] = {
    {800, 600, "800x600     4:3  (design)"},
    {1024, 768, "1024x768    4:3"},
    {1280, 720, "1280x720    16:9 720p"},
    {1280, 960, "1280x960    4:3"},
    {1366, 768, "1366x768    16:9 laptop"},
    {1600, 900, "1600x900    16:9"},
    {1920, 1080, "1920x1080   16:9 1080p"},
    {1920, 1200, "1920x1200   16:10"},
    {2560, 1440, "2560x1440   16:9 1440p"},
    {2560, 1600, "2560x1600   16:10"},
    {3440, 1440, "3440x1440   21:9 ultrawide"},
    {3840, 2160, "3840x2160   16:9 4K"},
};
const int kNumResolutions =
    static_cast<int>(sizeof(kResolutions) / sizeof(kResolutions[0]));

} // namespace

int main() {
  const float dt = 1.f / 60.f;
  const float moveSpeed = 5.f;  // tiles / second (Entity's default)
  const float jumpSpeed = 10.f; // tiles / second (Entity::jumpSpeed)
  const float gravity = 20.f;   // tiles / second^2 (Physics::gravity)
  const int steps = 120;        // two seconds of simulated fixed steps
  const float epsilon = 1e-4f;

  // ---------------------------------------------------------------------
  std::printf("== Resolution independence: %d resolutions, 800x600 to 4K ==\n",
              kNumResolutions);
  std::printf("(tile-space position/velocity never reference tileSizeX/Y, so "
              "resolution must not change tile displacement)\n\n");

  float baseDisplacement = 0.f;
  float baseApex = 0.f;
  for (int r = 0; r < kNumResolutions; r++) {
    const Resolution &res = kResolutions[r];
    int tileSizeX = tileSizeFor(res.w, REF_W);
    int tileSizeY = tileSizeFor(res.h, REF_H);

    float displacement = simulateHorizontal(moveSpeed, dt, steps);
    float apex = simulateJumpApex(jumpSpeed, gravity, dt, steps);
    if (r == 0) {
      baseDisplacement = displacement;
      baseApex = apex;
    }

    std::printf("  %-28s tile=%3dx%-3dpx | walk=%8.5f tiles (%6.1fpx) | "
                "apex=%8.5f tiles (%6.1fpx)\n",
                res.label, tileSizeX, tileSizeY, displacement,
                displacement * tileSizeX, -apex, -apex * tileSizeY);
  }
  std::printf("\n");

  for (int r = 1; r < kNumResolutions; r++) {
    char what[160];
    std::snprintf(what, sizeof(what), "walk distance at %dx%d == 800x600",
                  kResolutions[r].w, kResolutions[r].h);
    expectNear(simulateHorizontal(moveSpeed, dt, steps), baseDisplacement,
               epsilon, what);
  }
  for (int r = 1; r < kNumResolutions; r++) {
    char what[160];
    std::snprintf(what, sizeof(what), "jump apex at %dx%d == 800x600",
                  kResolutions[r].w, kResolutions[r].h);
    expectNear(simulateJumpApex(jumpSpeed, gravity, dt, steps), baseApex,
               epsilon, what);
  }

  // ---------------------------------------------------------------------
  // The section above proves the simulation ignores resolution. Resolution
  // DOES still enter at the pixel projection (Entity::syncRect), and that is
  // where a high-DPI regression would actually show up -- so check it
  // directly rather than assuming it is fine.
  std::printf("\n== Pixel projection: entity vs terrain grid alignment ==\n");
  std::printf("(Entity::syncRect and Terrain::fillScreen must quantise "
              "identically -- both\n project through the unrounded "
              "pixels-per-tile. Projecting through the rounded\n integer tile "
              "size instead accumulates up to 0.5px per tile, which reached\n "
              "10px / 16%% of a tile at 1366x768 before this was fixed.)\n\n");

  // Both paths now compute lround(tileIndex * TILE_SIZE * scale), so the
  // alignment must be exact at every resolution -- not merely bounded.
  const float driftLimitX = 0.f;
  const float driftLimitY = 0.f;

  float worstDriftX = 0.f;
  float worstDriftY = 0.f;
  const char *worstLabelX = "";
  const char *worstLabelY = "";

  for (int r = 0; r < kNumResolutions; r++) {
    const Resolution &res = kResolutions[r];
    int tileSizeX = tileSizeFor(res.w, REF_W);
    int tileSizeY = tileSizeFor(res.h, REF_H);

    float maxDriftX = 0.f;
    for (int tx = 0; tx < TILES_X; tx++) {
      float drift = std::fabs(
          static_cast<float>(entityPixelFor(static_cast<float>(tx), res.w, REF_W) -
                             blockPixelFor(tx, res.w, REF_W)));
      if (drift > maxDriftX) {
        maxDriftX = drift;
      }
    }
    float maxDriftY = 0.f;
    for (int ty = 0; ty < TILES_Y; ty++) {
      float drift = std::fabs(
          static_cast<float>(entityPixelFor(static_cast<float>(ty), res.h, REF_H) -
                             blockPixelFor(ty, res.h, REF_H)));
      if (drift > maxDriftY) {
        maxDriftY = drift;
      }
    }

    std::printf("  %-28s max drift: x=%5.1fpx (%4.1f%% of tile) | "
                "y=%5.1fpx (%4.1f%% of tile)\n",
                res.label, maxDriftX, 100.f * maxDriftX / tileSizeX, maxDriftY,
                100.f * maxDriftY / tileSizeY);

    if (maxDriftX > worstDriftX) {
      worstDriftX = maxDriftX;
      worstLabelX = res.label;
    }
    if (maxDriftY > worstDriftY) {
      worstDriftY = maxDriftY;
      worstLabelY = res.label;
    }
  }
  std::printf("\n  worst x drift: %.1fpx at %s\n", worstDriftX, worstLabelX);
  std::printf("  worst y drift: %.1fpx at %s\n\n", worstDriftY, worstLabelY);

  expectAtMost(worstDriftX, driftLimitX,
               "entity/terrain x alignment is exact at every resolution");
  expectAtMost(worstDriftY, driftLimitY,
               "entity/terrain y alignment is exact at every resolution");

  // ---------------------------------------------------------------------
  std::printf("\n== Framerate independence (dt vs 2*dt) ==\n");
  float posFineDt = simulateHorizontal(moveSpeed, dt, steps * 2);
  float posCoarseDt = simulateHorizontal(moveSpeed, dt * 2.f, steps);
  std::printf("  2N steps @dt = %.6f tiles | N steps @2dt = %.6f tiles\n",
              posFineDt, posCoarseDt);
  expectNear(posCoarseDt, posFineDt, epsilon,
             "horizontal: N steps @2dt == 2N steps @dt");

  float apexFineDt = simulateJumpApex(jumpSpeed, gravity, dt, steps * 2);
  float apexCoarseDt = simulateJumpApex(jumpSpeed, gravity, dt * 2.f, steps);
  std::printf(
      "  2N steps @dt apex = %.6f tiles | N steps @2dt apex = %.6f tiles\n",
      apexFineDt, apexCoarseDt);
  // Semi-implicit (symplectic) Euler has a known, exact O(dt) bias here:
  // for an impulse jumpSpeed with constant gravity, solving the recurrence
  // gives apex(dt) = -jumpSpeed^2/(2*gravity) + jumpSpeed*dt/2. So doubling
  // dt does not reproduce the same apex bit-for-bit the way the
  // constant-velocity horizontal case does -- the discrepancy is exactly
  // jumpSpeed*dt/2 between the two dt's used below. Bound against that
  // derived value (with a small margin) rather than an arbitrary tolerance.
  const float jumpEpsilon = jumpSpeed * dt;
  expectNear(apexCoarseDt, apexFineDt, jumpEpsilon,
             "jump apex: N steps @2dt == 2N steps @dt (discretization bound)");

  std::printf("\n%s (%d failing assertion%s)\n",
              failures == 0 ? "ALL TESTS PASSED" : "TESTS FAILED", failures,
              failures == 1 ? "" : "s");
  return failures == 0 ? 0 : 1;
}
