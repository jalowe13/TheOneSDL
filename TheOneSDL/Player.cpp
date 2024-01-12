/*
* Player.h
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

#include "Player.h"

Player::Player(SDL_Renderer *renderer, int x, int y) // Define the constructor
    : Entity(renderer, x, y) {
  std::cout << "Spawning Player at " << x << ", " << y << "\n";
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
  //
  // This Entity Handle movement should actually pass in a datastructure of all
  // specific textures to load for each instance in order
  //
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
