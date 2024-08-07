/*
* Physics.cpp
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
#include "Physics.h"
#include "Terrain.h"
const std::string Physics::floor = "Floor";

Physics::Physics() {
  std::cout << "-----Start Physics Engine\n";

  std::cout << "-----Physics Engine Started\n";
}

Physics::~Physics() {
  std::cout << "-----Stopping Physics Engine" << std::endl;
}

float Physics::getGravity() { return gravity; }

void Physics::incTime() { time = time + (timeI * 2); }

void Physics::resetTime() { time = 0.0; }

float Physics::getTime() { return time; }

// Static collision handling
// SDL_Rect *A is the hitbox of the object
// Terrain *terrain is the terrain object
// Returns 0 if no collision
// Returns 1 if on top of block
// Returns 2 if to the left of block
// Returns 3 if to the right of block
// Returns 4 if under a block
// Returns 5 if unknown collision error
int Physics::checkRectCollision(SDL_Rect *A, Terrain *terrain) {
  std::vector<Block> *blocks = terrain->getBlockVector();
  for (Block block : *blocks) // Iterate through every block
  {
    if (SDL_HasIntersection(
            A,
            block.get_Rect())) // Check if its intersecting with another hitbox
    {
      // Only Check Collision not by direction
      if (floor == block.name) // If on Floor return Code for on top of block
      {
        // char direction = get4Points(A,block.getX(),block.getY());

        if (block.getY() > A->y) // If On top of block
        {
          return 1;
        }
        if (block.getX() < A->x) // If to the left of a block
        {
          if (block.getY() < (A->y - 20)) // But under another one
          {
            return 4;
          }
          return 2;
        } else if (block.getX() > A->x) // If to the right of a block
        {
          if (block.getY() < (A->y - 20)) // But under a block
          {
            return 4;
          }
          return 3;
        }
        return 5; // Unknown collision error
      }
    }
  }
  return 0;
}
// Dynamic Collision Detection for entities
// Checks for collision between entities
// If collision detected, end game
// Entity *entity is the entity to check for collision
// EntityManager *manager is the manager that holds all entities
void Physics::checkEntityCollision(Entity *entity, EntityManager *manager) {
  for (auto &entity2 :
       manager->getEntities()) { // For every entity in entity list
    if (entity->getEntityType() !=
        entity2->getEntityType()) { // If not the same type
      if (SDL_HasIntersection(entity->getHitboxRect(),
                              entity2->getHitboxRect())) { // If intersecting
        // std::cout << "Collision between " << entity->getEntityType() << " and
        // "
        //           << entity2->getEntityType() << std::endl;
        std::cout << "\n\n\n--------------------------------\n";
        std::cout << "            GAME OVER\n";
        std::cout << "--------------------------------\n";
        SDL_Delay(3000);
        exit(1);
      }
    }
  }
}

// Note: Not used
// Utility function for something? Later on
// Try not to pass pointers when you dont need to
char Physics::get4Points(SDL_Rect *A, int centerX, int centerY) {
  // A points p1
  float A_centerX, A_centerY;
  A_centerX = A->x + 16;
  A_centerY = A->y + 16;
  // std::cout << "[" << A_centerX << "," << A_centerY << "] ";
  // std::cout << " " << A_centerX << "," << A_centerY << " " << centerX << " "
  // << centerY << "\r";

  // B Points of interest
  int B_NorthY = centerY;
  int B_SouthY = centerY + 32;
  int B_EastX = centerX;
  int B_WestX = centerX + 32;

  // p2
  std::pair<int, int> north = {centerX + 16, B_NorthY};
  std::pair<int, int> south = {centerX + 16, B_SouthY};
  std::pair<int, int> east = {B_EastX, centerY + 16};
  std::pair<int, int> west = {B_WestX, centerY + 16};

  // Distance Calculations
  // p1.x p2.x , p1.y p2.y
  float dist_N =
      sqrt(pow(A_centerX - north.first, 2) + pow(A_centerY - north.second, 2));
  float dist_S =
      sqrt(pow(A_centerX - south.first, 2) + pow(A_centerY - south.second, 2));
  float dist_E =
      sqrt(pow(A_centerX - east.first, 2) + pow(A_centerY - east.second, 2));
  float dist_W =
      sqrt(pow(A_centerX - west.first, 2) + pow(A_centerY - west.second, 2));
  // std::cout << "Center[" << A_centerX << "," << A_centerY << "]\n";
  // std::cout << "N[" << dist_N << "]S[" << dist_S << "]E[" << dist_E << "]W["
  // << dist_W << "] ";

  // Finding minimum distance
  float mindist = dist_N;
  char direction = 'N';

  if (dist_S < mindist) {
    mindist = dist_S;
    direction = 'S';
  }
  if (dist_E < mindist) {
    mindist = dist_E;
    direction = 'E';
  }
  if (dist_W < mindist) {
    mindist = dist_W;
    direction = 'W';
  }

  // mindist = (dist_S < mindist) ? dist_S : mindist;
  // direction = (dist_S < mindist) ? "South" : direction;
  // mindist = (dist_E < mindist) ? dist_E : mindist;
  // direction = (dist_E < mindist) ? "East" : direction;
  // mindist = (dist_W < mindist) ? dist_W : mindist;
  // direction = (dist_W < mindist) ? "West" : direction;

  // std::cout << " Direction is " << direction << " ";

  // std::cout << "" << A_centerX << "," << A_centerY << " " << centerX << " "
  // << centerY << "\r";
  return direction;
}
