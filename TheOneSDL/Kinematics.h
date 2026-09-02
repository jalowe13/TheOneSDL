/*
* Kinematics.h
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
#pragma once

// Pure, SDL-free tile-space kinematics. This is the one piece of the
// movement pipeline that must never depend on SDL/engine types: it is what
// Entity's fixed-timestep movement is built on, and it is exactly what the
// headless test (test_kinematics.cpp) links against to prove that movement
// is resolution- and framerate-independent, without needing a window.
//
// All positions are in tile units (fractional) and all velocities are in
// tiles per second. Pixels only exist as a render-time projection computed
// elsewhere (Entity::syncRect): entityR.x = lround(pos_x * tileSizeX).

namespace Kinematics {

// Advance a position by one fixed timestep given a constant velocity.
inline float stepPosition(float pos, float velocity, float dt) {
  return pos + velocity * dt;
}

// Advance a velocity by one fixed timestep given a constant acceleration
// (e.g. gravity, in tiles/second^2).
inline float stepVelocity(float velocity, float acceleration, float dt) {
  return velocity + acceleration * dt;
}

} // namespace Kinematics
