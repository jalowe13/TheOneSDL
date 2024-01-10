#include "Entity.h"
#include <cmath>

Entity::Entity(SDL_Renderer *renderer, int x, int y) {
  // Rectangles
  entityR.h = 32;
  entityR.w = 32;
  tilemap_x = x;
  tilemap_y = y;
  entityR.x = tilemap_x * 32;
  entityR.y = tilemap_y * 32;

  // Hitbox
  hitboxOn = false;
  entityHitboxR.h = 20;
  entityHitboxR.w = 12;
  entityHitboxR.x = entityR.x + 10;
  entityHitboxR.y = entityR.y + 10;
  // Set Entity defaults
  entitySpeed = 3;
  entityFalling = false;
  // Defaults zero no texture loaded yet
  textureWidth = 0;
  textureHeight = 0;
  frameWidth = textureWidth / 60;
  frameHeight = textureHeight;
  frame_time = 0;

  // Load Textures
  // Load filenames
  std::cout << "Loading Entity Textures...\n";

  editMS(3); // push default speed

  std::cout << "-----Entity Created\n";
}

Entity::~Entity() { std::cout << "-----Entity Destroyed\n"; }

// Getters
const float Entity::getSpeed() { return movementModifier; }

Entity::MovementDirection Entity::xPath() { return currentDirectionX; }

Entity::MovementDirection Entity::yPath() { return currentDirectionY; }

int Entity::getX() { return entityR.x; }

int Entity::getTexX() { return textureR.x; }

int Entity::getTileX() { return getX() / 32; }

SDL_Texture *Entity::getTexture() { return entity_texture; }

int Entity::getY() { return entityR.y; }

int Entity::getTileY() { return getY() / 32; }

float Entity::getMS() { return movementModifier; }

SDL_Rect *Entity::getRect() { return &entityR; }

SDL_Rect *Entity::getRectTex() { return &textureR; }

bool Entity::hitboxCheck() {
  // Update position
  entityHitboxR.x = entityR.x + 10;
  entityHitboxR.y = entityR.y + 10;
  return hitboxOn;
}

SDL_Rect *Entity::getHitboxRect() { return &entityHitboxR; }

// Setters

void Entity::xPathEdit(MovementDirection path) { currentDirectionX = path; }

void Entity::yPathEdit(MovementDirection path) { currentDirectionY = path; }

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
  tilemap_x = x;
  tilemap_y = y;
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
    std::cout << entityType << ": Texture loaded " << name
              << " with path:" << filename << " with dims " << textureWidth
              << " and " << textureHeight << std::endl;
    if (textures[name] == 0 || textureWidth == 0 || textureHeight == 0) {
      std::cout << "!!!!!" << name << " failed to load from path " << filename
                << "!!!!!" << std::endl;
      exit(-1);
    }
  }
  std::cout << "Textures done loading\n";
}

// Updating Texture per frame time

void Entity::updateTexture(Physics *phys_eng, Terrain *terrain_eng) {
  xTexEdit(getTexX() + frameWidth);
  if (getTexX() >= textureWidth) // Reset back to the end of the texture
  {
    xTexEdit(0);
  }
  if (frame_time >
      60) // Unknown why this frametime feature exists, investigate further
  {
    frame_time = 0;
  } else {
    handleMovement(phys_eng, terrain_eng);
    frame_time++;
  }
}

void Entity::checkCollision(int i, Physics *phys_eng) {
  if (entityType == EntityType::PLAYER_E) {
    switch (i) {
    case 0:                // Falling
      phys_eng->incTime(); // Increase time when away from ground
      yEdit(getY() + phys_eng->getGravity() * phys_eng->getTime());
      // std::cout << "Air Time: " << phys_eng->getTime() << "\r";
      isColliding = false;
      break;
    case 1: // Colliding Ground
      entityFalling = false;
      phys_eng->resetTime(); // Reset time on ground
      isColliding = false;
      // std::cout << "~~~Collide~~~\r";
      break;
    case 2: // Colliding from left
      isColliding = true;
      xEdit(getX() + getSpeed() + 4);
      break;
    case 3: // Colliding from right
      isColliding = true;
      xEdit(getX() - getSpeed() - 4);
      break;
    case 4: // Colliding from below
      isColliding = true;
      yEdit(getY() + getSpeed() + 4);
      break;
    }
  }
}

void Entity::handleMovement(Physics *phys_eng, Terrain *terrain_eng) {
  if (boundsCheck(getX(), getY())) {
    switch (xPath()) {
    case Left: {
      (!isColliding) ? xEdit(getX() - getSpeed()) : xEdit(getX() + getSpeed());
      break;
    }
    case Right: {
      (!isColliding) ? xEdit(getX() + getSpeed()) : xEdit(getX() - getSpeed());
      break;
    }
    default: {
      // std::cout << "Unknown call in handle movement in x direction
      // 'None'\n"; exit(1);
    }
    }
    switch (yPath()) {
    case Up: {
      if (!entityFalling) {
        (!isColliding) ? yEdit(getY() - getSpeed())
                       : yEdit(getY() + getSpeed());
      }
      break;
    }
    case None: // No input
    {
      entityFalling = true;
    }
    default: {
      // std::cout << "Unknown call in handle movement in y direction
      // 'None'\n"; exit(1);
    }
    }
    // Set tilemap cords
    tilemap_x = round(getX() / 32);
    tilemap_y = round(getY() / 32);
  } else { // Not in bounds
    switch (xPath()) {
    case Right: {
      xEdit(getX() - getSpeed());
      if (entityType == EntityType::ENEMY_E) {
        xPathEdit(MovementDirection::Left);
        looking = LookingDirection::LookLeft;
        inAnimation = false;
      }
      break;
    }
    case Left: {
      xEdit(getX() + getSpeed());
      if (entityType == EntityType::ENEMY_E) {
        xPathEdit(MovementDirection::Right);
        looking = LookingDirection::LookRight;
        inAnimation = false;
      }
      break;
    }
    default: {
      // std::cout << "Unknown call in bounds check in x direction
      // 'None'\n"; exit(1);
    }
    }
    switch (yPath()) {
    case Down: {
      yEdit(getY() + getSpeed());
      break;
    }
    case Up: {
      yEdit(getY() - getSpeed());
      break;
    }
    default: {
      // std::cout << "Unknown call in bounds check in y direction
      // 'None'\n"; exit(1);
    }
    }
    // Out of bounds check and reset
    xEdit(getX() + (getX() >= SCREEN_WIDTH ? -getSpeed()
                    : getX() <= 0          ? getSpeed()
                                           : 0));
    yEdit(getY() + (getY() >= SCREEN_HEIGHT ? -getSpeed()
                    : getY() <= 0           ? getSpeed()
                                            : 0));
  }
}

bool Entity::boundsCheck(int x, int y) {
  if ((x > 0 && y > 0) && ((x < SCREEN_WIDTH) && (y < SCREEN_HEIGHT))) {
    return true;
  }
  return false;
}
