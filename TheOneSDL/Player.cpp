#include "Player.h"

Player::Player(SDL_Renderer *renderer, int x, int y)
    : Entity(renderer, x, y, Entity::EntityType::Player) {
  std::cout << "Player Created\n";
}

Player::~Player() {
  // Destructor implementation
}