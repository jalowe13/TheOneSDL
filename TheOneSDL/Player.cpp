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
void Player::handleMovement(Physics *phys_eng, Terrain *terrain_eng) {
  // Handle Generics of cord movement
  Entity::handleMovement(phys_eng, terrain_eng);
  //  Handle player movement animations
  switch (xPath()) {
  case Left: {
    looking = LookLeft;
    if (!inAnimation) {
      setTexture(textures["run_left"]);
      inAnimation = true;
    }
    break;
  }
  case Right: {
    looking = LookRight;
    if (!inAnimation) {
      setTexture(textures["run_right"]);
      inAnimation = true;
    }
    break;
  }
  case None: {
    if (inAnimation) {
      switch (looking) {
      case LookLeft:
        setTexture(textures["idle_left"]);
        break;
      case LookRight:
        setTexture(textures["idle_right"]);
        break;
      }
      inAnimation = false;
    }
  }
  default: {
    break;
  }
  }
  switch (yPath()) {
  case Up: {
    // Jumping Animation
    break;
  }
  case Down: {
    // Sitting Animation
    if (!inAnimation) {
      setTexture(textures["sit"]);
      inAnimation = true;
    }
    break;
  }
  default: {
    break;
  }
  }
}
std::list<std::string> Player::getTexturePaths() { return tex_files; }

std::list<std::string> Player::getTextureNames() { return tex_names; }

Player::~Player() {
  // Destructor implementation
}