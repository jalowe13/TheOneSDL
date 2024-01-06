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
}

std::list<std::string> Enemy::getTexturePaths() { return tex_files; }

std::list<std::string> Enemy::getTextureNames() { return tex_names; }

Enemy::~Enemy() {
  // Destructor implementation
}