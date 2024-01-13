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

#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player : public Entity {
  // Add player-specific members and functions here
public:
  Player(SDL_Renderer *renderer, int x,
         int y); // Declare the constructor // Constructor
  ~Player();     // Destructor
  void handleMovement(Physics *phys_eng, Terrain *terrain_eng,
                      SDL_Window *window) override;
  std::list<std::string> getTexturePaths(); // Texture file paths
  std::list<std::string> getTextureNames(); // Texture file names
private:
  // Texture Paths
  std::string idle_left = "textures/VGB/idle/vgb_idle-left-Sheet.png";
  std::string idle_right = "textures/VGB/idle/vgb_idle-right-Sheet.png";
  std::string run_left = "textures/VGB/run/vgb_run_left-Sheet.png";
  std::string run_right = "textures/VGB/run/vgb_run_right-Sheet.png";
  std::string sit = "textures/VGB/idle/vgb_gamer_idle-Sheet.png";
  // Texture Data Structures
  std::list<std::string> tex_files = {idle_left, idle_right, run_left,
                                      run_right, sit};
  std::list<std::string> tex_names = {"idle_left", "idle_right", "run_left",
                                      "run_right", "sit"};
};
