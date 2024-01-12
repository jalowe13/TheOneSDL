/*
 * Enemy.h
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

#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Enemy : public Entity {
  // Add Enemy-specific members and functions here
public:
  Enemy(SDL_Renderer *renderer, int x,
        int y); // Declare the constructor // Constructor
  ~Enemy();     // Destructor
  bool hitboxCheck() override;
  void handleMovement(Physics *phys_eng, Terrain *terrain_eng) override;
  std::list<std::string> getTexturePaths(); // Texture file paths
  std::list<std::string> getTextureNames(); // Texture file names
private:
  // Texture Paths
  std::string chomper_idle_left =
      "textures/enemy/chomper/chompter_idle-left.png";
  std::string chomper_idle_right =
      "textures/enemy/chomper/chompter_idle-right.png";
  std::string chomper_move_left =
      "textures/enemy/chomper/Chomper_Move-Left.png";
  std::string chomper_move_right =
      "textures/enemy/chomper/Chomper_Move-Right.png";
  // Texture Data Structures
  std::list<std::string> tex_files = {chomper_idle_left, chomper_idle_right,
                                      chomper_move_left, chomper_move_right};
  std::list<std::string> tex_names = {"chomper_idle_left", "chomper_idle_right",
                                      "chomper_move_left", "chomper_move_right",
                                      "run_right",         "sit"};
  int idle_timer = rand() % 120 + 1;
};
