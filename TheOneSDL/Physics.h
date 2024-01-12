/*
* Physics.h
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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

// Forward declare
class Terrain;
class Player;
class Entity;
class EntityManager;

class Physics {
public:
  Physics();
  ~Physics();
  // Global Gravity return
  float getGravity();

  // Block Types
  static const std::string floor;

  // Start a float timer
  void incTime();
  // End and reset float timer
  void resetTime();
  // Get the amount of time
  float getTime();

  /*
  Check Rectangle Collision, extension of SDL2
  Check if A is colliding with something on the tilemap
  Return true if true false if not
  SDL_Rect* A - Rectangle A (Player or entity)
  Terrain* terrain - Reference to the running terrain generation

  Returns integer code of kind of collision
  0 -
  */
  int checkRectCollision(SDL_Rect *A, Terrain *terrain);
  /*
   * Check if Entity is colliding with any Entity on the tilemap in the
   * EntityList
   * Return true if true false if not
   * Entity* entity - Entity A (Player or entity)
   * EntityManager* manager - Reference to the running EntityManager
   */

  void checkEntityCollision(Entity *entity, EntityManager *manager);
  /*
  Given two rectangles find distances from
  Rectangle A to all 4 points on Rectangle B
  to figure out which direction Rectangle A is approaching from

  SDL_Rect* A - Rectangle A
  int centerX - Rectangle B center X
  int centerY - Rectangle B center Y

  Return char - Direction approaching from [N,S,E,W] - [0,1,2,3]
  */
  char get4Points(SDL_Rect *A, int centerX, int centerY);

private:
  const float gravity = 0.90; // Would be .98 but cannot reach above 2 blocks
  const float timeI = .05;
  const float jumpForgiveness =
      0; // Skew for landing on top of a tile: Higher will forgive more
  float time = 0.0;
};
