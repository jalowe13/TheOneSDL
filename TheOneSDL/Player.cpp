#include "Player.h"

Player::Player(SDL_Renderer *renderer, int x, int y) // Define the constructor
    : Entity(renderer, x, y) {
  entityType = EntityType::PLAYER_E;
  Entity::tex_names = getTextureNames();
  Entity::tex_files = getTexturePaths();
  std::cout << "Player Created\n";
  loadTextures(renderer);
  if (textures.find("idle_right") == textures.end()) {
    throw std::runtime_error("Texture 'idle_right' does not exist.");
  }
  setTexture(textures["idle_right"]);
}

std::list<std::string> Player::getTexturePaths() { return tex_files; }

std::list<std::string> Player::getTextureNames() { return tex_names; }

Player::~Player() {
  // Destructor implementation
}