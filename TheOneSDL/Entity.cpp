/*
 * Entity.cpp
* Copyright (C) [2024] [Jacob Lowe]
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
#include "Entity.h"
#include "Kinematics.h"

Entity::Entity(SDL_Renderer *renderer, int x, int y) {
  // Tile space is the unit of truth: x,y are tile coordinates.
  pos_x = static_cast<float>(x);
  pos_y = static_cast<float>(y);
  vel_x = 0.f;
  vel_y = 0.f;
  // Rectangles
  entityR.w = tileSizeX;
  entityR.h = tileSizeY;
  syncRect();
  std::cout << "Entity Spawned at " << entityR.x << "," << entityR.y << "\n";
  // Hitbox
  hitboxOn = false;
  hitboxCheck(); // compute entityHitboxR from entityR at the current scale
  entityFalling = false;
  // Defaults zero no texture loaded yet
  textureWidth = 0;
  textureHeight = 0;
  frameWidth = textureWidth / 60;
  frameHeight = textureHeight;
  frame_time = 0.f;

  // Load Textures
  // Load filenames
  std::cout << "Loading Entity Textures...\n";

  editMS(5.f); // default move speed, tiles / second

  std::cout << "-----Entity Created\n";
}

Entity::~Entity() { std::cout << "-----Entity Destroyed\n"; }

// Getters
const float Entity::getSpeed() { return movementModifier; }

Entity::MovementDirection Entity::xPath() { return currentDirectionX; }

Entity::MovementDirection Entity::yPath() { return currentDirectionY; }

int Entity::getX() { return entityR.x; }

int Entity::getTexX() { return textureR.x; }

SDL_Texture *Entity::getTexture() { return entity_texture; }

int Entity::getY() { return entityR.y; }

// Tile coordinates are the source of truth: no pixel math, no scale mixing.
int Entity::getTileX() { return static_cast<int>(pos_x); }
int Entity::getTileY() { return static_cast<int>(pos_y); }

float Entity::getMS() { return movementModifier; }

SDL_Rect *Entity::getRect() { return &entityR; }

SDL_Rect *Entity::getRectTex() { return &textureR; }

bool Entity::hitboxCheck() {
  // Hitbox inset/size, expressed as fractions of a tile so they scale with
  // tileSizeX/Y exactly like scaleTextures does -- one formula, no more
  // hardcoded-pixel offsets overwriting the scaled ones every step.
  float scalex = tilePixelsX / static_cast<float>(TILE_SIZE);
  float scaley = tilePixelsY / static_cast<float>(TILE_SIZE);
  entityHitboxR.x = entityR.x + static_cast<int>(std::lround(10.f * scalex));
  entityHitboxR.y = entityR.y + static_cast<int>(std::lround(8.f * scaley));
  entityHitboxR.w = static_cast<int>(std::lround(12.f * scalex));
  entityHitboxR.h = static_cast<int>(std::lround(20.f * scaley));
  return hitboxOn;
}

SDL_Rect *Entity::getHitboxRect() { return &entityHitboxR; }

// Setters
bool &Entity::hitBoxToggle() {
  hitboxOn = !hitboxOn;
  return hitboxOn;
}

void Entity::xPathEdit(MovementDirection path) { currentDirectionX = path; }

void Entity::yPathEdit(MovementDirection path) {
  // Jump is an edge-triggered impulse: only fires on the transition into Up
  // while grounded, so holding the key doesn't add velocity every frame and
  // OS key-repeat can't re-trigger it. Gravity (checkCollision, case 0)
  // takes over from here every fixed step.
  if (path == Up && currentDirectionY != Up && !entityFalling) {
    vel_y = -jumpSpeed;
    entityFalling = true;
  }
  currentDirectionY = path;
}

void Entity::xEdit(int x) { entityR.x = x; }

void Entity::yEdit(int y) { entityR.y = y; }

void Entity::wEdit(int w) { entityR.w = w; }

void Entity::hEdit(int h) { entityR.h = h; }

void Entity::xTexEdit(int x) { textureR.x = x; }

void Entity::yTexEdit(int y) { textureR.y = y; }

void Entity::wTexEdit(int w) { textureR.w = w; }

void Entity::hTexEdit(int h) { textureR.h = h; }

void Entity::editMS(float speed) { movementModifier = speed; }

void Entity::setTexture(SDL_Texture *texture) {
  entity_texture = texture;
  SDL_QueryTexture(entity_texture, NULL, NULL, &textureWidth, &textureHeight);
  frameWidth = textureWidth / 60;
  frameHeight = textureHeight;
  xTexEdit(0);
  yTexEdit(0);
  wTexEdit(frameWidth);
  hTexEdit(frameHeight);
}

void Entity::set_tilemap_pos(int x, int y) {
  pos_x = static_cast<float>(x);
  pos_y = static_cast<float>(y);
  syncRect();
}

// Projects tile-space position onto the pixel rect used for rendering and
// collision. This is the ONLY place pixels are derived from tiles.
void Entity::syncRect() {
  entityR.w = tileSizeX;
  entityR.h = tileSizeY;
  // Project through the UNROUNDED pixels-per-tile so this lands on exactly
  // the same pixel Terrain::fillScreen uses for the block at this tile.
  xEdit(static_cast<int>(std::lround(pos_x * tilePixelsX)));
  yEdit(static_cast<int>(std::lround(pos_y * tilePixelsY)));
}

// Methods
void Entity::loadTextures(SDL_Renderer *renderer) {
  std::cout << "Load Textures\n";
  const char *filename; // Filename to load
  SDL_Texture *texture; // Default texture pointer
  while (tex_files.size() > 0) {
    std::string new_file = tex_files.front().c_str(); // Reference from front
    filename = new_file.c_str();
    std::string name = tex_names.front();
    tex_names.pop_front(); // pop
    tex_files.pop_front();
    texture = IMG_LoadTexture(renderer, filename);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    textures[name] = texture;
    // std::cout << entityType << ": Texture loaded " << name
    //           << " with path:" << filename << " with dims " << textureWidth
    //           << " and " << textureHeight << std::endl;
    if (textures[name] == 0 || textureWidth == 0 || textureHeight == 0) {
      std::cout << "!!!!!" << name << " failed to load from path " << filename
                << "!!!!!" << std::endl;
      exit(-1);
    }
  }
  std::cout << "Textures done loading\n";
}

// Advances sprite-sheet animation by elapsed wall-clock time, independent of
// render call rate (and independent of movement, which happens elsewhere).
void Entity::updateTexture(float deltaSeconds) {
  frame_time += deltaSeconds;
  while (frame_time >= FRAME_INTERVAL) {
    frame_time -= FRAME_INTERVAL;
    xTexEdit(getTexX() + frameWidth);
    if (getTexX() >= textureWidth) // Reset back to the end of the texture
    {
      xTexEdit(0);
    }
  }
}
void Entity::scaleTextures(SDL_Window *window) {
  std::cout << "Scale Textures for " << entityType << std::endl;
  int current_width, current_height;
  SDL_GetWindowSize(window, &current_width, &current_height);
  float scalex = current_width / static_cast<float>(SCREEN_WIDTH);
  float scaley = current_height / static_cast<float>(SCREEN_HEIGHT);
  tilePixelsX = TILE_SIZE * scalex; // unrounded: matches Terrain::fillScreen
  tilePixelsY = TILE_SIZE * scaley;
  tileSizeX = static_cast<int>(std::lround(tilePixelsX));
  tileSizeY = static_cast<int>(std::lround(tilePixelsY));
  // Tile position (pos_x/pos_y) never changes on resize -- only the pixel
  // projection does. Refresh entityR and the hitbox immediately so a resize
  // is visible even on a frame with no physics step.
  syncRect();
  hitboxCheck();
}
void Entity::toggleDirection() {
  if (currentDirectionX == MovementDirection::Left) {
    xPathEdit(MovementDirection::Right); // Change direction
    looking = LookingDirection::LookRight;
    inAnimation = false;
  } else {
    xPathEdit(MovementDirection::Left); // Change direction
    looking = LookingDirection::LookLeft;
    inAnimation = false;
  }
}
// Check Collision and return isColliding if colliding with an object
// Also adjusts impact need be to teleport back entity if in object
// dt is the fixed physics timestep (seconds) this call resolves.
void Entity::checkCollision(int i, Physics *phys_eng, float dt) {
  // Falling and landing are per-entity now (vel_y is this entity's own fall
  // state) and apply to every entity type -- enemies fall too.
  switch (i) {
  case 0: // No ground contact: mark airborne. Integration itself happens in
          // handleMovement, which runs every fixed step regardless of contact.
    entityFalling = true;
    // Per-step console I/O; this runs every fixed step for every entity.
    isColliding = false;
    break;
  case 1: // Colliding Ground
    // Only treat this as "landing" if we were moving downward (or at rest).
    // A jump's upward impulse and a same-tick stale ground contact must not
    // cancel each other out.
    if (vel_y >= 0.f) {
      entityFalling = false;
      vel_y = 0.f;
      // Per-step console I/O removed (see above).
    }
    isColliding = false;
    break;
  default:
    break;
  }

  if (entityType == EntityType::PLAYER_E) {
    switch (i) {
    case 2: // Colliding from left
      isColliding = true;
      pos_x += getSpeed() * dt;
      break;
    case 3: // Colliding from right
      isColliding = true;
      pos_x -= getSpeed() * dt;
      break;
    case 4: // Colliding from below
      isColliding = true;
      pos_y += getSpeed() * dt;
      break;
    default:
      break;
    }
  } else if (entityType == EntityType::ENEMY_E) {
    const float bouncebackTiles =
        4.f / TILE_SIZE; // How far to set back the entity if colliding
    switch (i) {
    case 2: { // Colliding from left
      isColliding = true;
      pos_x += getSpeed() * dt + bouncebackTiles;
      toggleDirection();
      break;
    }
    case 3: { // Colliding from right
      isColliding = true;
      pos_x -= getSpeed() * dt + bouncebackTiles;
      toggleDirection();
      break;
    }
    default:
      isColliding = false; // Other collisions like sitting on top of a block
      break;
    }
  }

  // Keep the pixel rect and hitbox in step with the position this resolve
  // step just settled on, so the very next entity-vs-entity check (and this
  // frame's render, if this was the last fixed step) sees the current state.
  syncRect();
  hitboxCheck();
}

void Entity::handleMovement(Physics *phys_eng, Terrain *terrain_eng,
                            float dt) {
  (void)terrain_eng; // reserved: handleMovement itself needs no terrain state
  if (boundsCheck(pos_x, pos_y)) {
    switch (xPath()) {
    case Left: {
      vel_x = isColliding ? getSpeed() : -getSpeed();
      pos_x = Kinematics::stepPosition(pos_x, vel_x, dt);
      break;
    }
    case Right: {
      vel_x = isColliding ? -getSpeed() : getSpeed();
      pos_x = Kinematics::stepPosition(pos_x, vel_x, dt);
      break;
    }
    default: {
      vel_x = 0.f;
    }
    }
    // Vertical motion is integrated HERE, every fixed step, so that a jump
    // impulse can actually lift the entity off the ground. Doing it only in
    // checkCollision's "falling" case deadlocks: leaving the ground requires
    // integration, but integration only ran once you had already left.
    // Gravity is skipped while grounded so a resting entity doesn't creep
    // down into the tile it is standing on.
    if (entityFalling) {
      vel_y = Kinematics::stepVelocity(vel_y, phys_eng->getGravity(), dt);
      pos_y = Kinematics::stepPosition(pos_y, vel_y, dt);
    }
  } else { // Not in bounds the entity is out of bounds
    // Per-step console I/O removed (see above).
    switch (xPath()) {
    case Right: {
      pos_x -= getSpeed() * dt;
      if (entityType == EntityType::ENEMY_E) {
        xPathEdit(MovementDirection::Left);
        looking = LookingDirection::LookLeft;
        inAnimation = false;
      }
      break;
    }
    case Left: {
      pos_x += getSpeed() * dt;
      if (entityType == EntityType::ENEMY_E) {
        xPathEdit(MovementDirection::Right);
        looking = LookingDirection::LookRight;
        inAnimation = false;
      }
      break;
    }
    default: {
    }
    }
    switch (yPath()) {
    case Down: {
      pos_y += getSpeed() * dt;
      break;
    }
    case Up: {
      pos_y -= getSpeed() * dt;
      break;
    }
    default: {
    }
    }
    // Out of bounds check and reset, in tile space against the playable grid.
    if (pos_x >= TILEMAP_TILES_X - 1.f) {
      pos_x -= getSpeed() * dt;
    } else if (pos_x <= 0.f) {
      pos_x += getSpeed() * dt;
    }
    if (pos_y >= TILEMAP_TILES_Y - 1.f) {
      pos_y -= getSpeed() * dt;
    } else if (pos_y <= 0.f) {
      pos_y += getSpeed() * dt;
    }
  }
  syncRect();
  hitboxCheck(); // keep the collision hitbox current for this same fixed step
}

bool Entity::boundsCheck(float x, float y) {
  if ((x > 0.f && y > 0.f) && ((x < (TILEMAP_TILES_X - 1.f)) &&
                               (y < (TILEMAP_TILES_Y - 1.f)))) {
    return true;
  }
  return false;
}
