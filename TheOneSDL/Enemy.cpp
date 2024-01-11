#include "Enemy.h"

Enemy::Enemy(SDL_Renderer *renderer, int x, int y) // Define the constructor
    : Entity(renderer, x, y) {
  entityType = EntityType::ENEMY_E;
  Entity::tex_names = getTextureNames();
  Entity::tex_files = getTexturePaths();
  std::cout << "Enemy Created\n";
  loadTextures(renderer);
  if (textures.find("chomper_idle_left") == textures.end()) {
    throw std::runtime_error("Texture 'chomper_idle_left' does not exist.");
  }
  xPathEdit(Entity::Left);
  setTexture(textures["chomper_idle_left"]);
  // Hitbox for Enemy
  entityHitboxR.w = 30;
}

bool Enemy::hitboxCheck() {
  // Update position
  entityHitboxR.x = entityR.x;
  entityHitboxR.y = entityR.y + 10;
  return hitboxOn;
}

void Enemy::handleMovement(Physics *phys_eng, Terrain *terrain_eng) {
  Entity::handleMovement(phys_eng, terrain_eng);
  if (idle_timer > 0) {
    idle_timer--;
  } else {
    idle_timer = rand() % 500 + 1;
    if (xPath() == Left || xPath() == Right) {
      xPathEdit(None);
    } else if (xPath() == None) {
      xPathEdit(Left);
    }
    inAnimation = false;
  }
  //  Handle player movement animations
  // Handle Generics of cord movement
  //
  // This Entity Handle movement should actually pass in a datastructure of all
  // specific textures to load for each instance in order
  switch (xPath()) {
  case Left: {
    looking = LookLeft;
    if (!inAnimation) {
      setTexture(textures["chomper_move_left"]);
      inAnimation = true;
    }
    break;
  }
  case Right: {
    looking = LookRight;
    if (!inAnimation) {
      setTexture(textures["chomper_move_right"]);
      inAnimation = true;
    }
    break;
  }
  case None: {
    if (!inAnimation) {
      switch (looking) {
      case LookLeft:
        setTexture(textures["chomper_idle_left"]);
        inAnimation = true;
        break;
      case LookRight:
        setTexture(textures["chomper_idle_right"]);
        inAnimation = true;
        break;
      }
    }
  }
  default: {
    break;
  }
  }
}

std::list<std::string> Enemy::getTexturePaths() { return tex_files; }

std::list<std::string> Enemy::getTextureNames() { return tex_names; }

Enemy::~Enemy() {
  // Destructor implementation
  std::cout << "Enemy Destroyed\n";
}
