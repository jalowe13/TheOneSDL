/*
 * EntityManager.h
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

#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include <vector>

class EntityManager {
public:
  EntityManager();
  ~EntityManager();
  void createAndAddEntity(SDL_Renderer *renderer, Entity::EntityType type,
                          int x, int y);
  void scaleEntities(SDL_Window *window);
  void addEntity(std::unique_ptr<Entity> entity);
  //   void destroyEntity(int entityId);
  int getEntityCount();
  std::vector<std::unique_ptr<Entity>> &getEntities();
  // Add your member function declarations here

private:
  std::vector<std::unique_ptr<Entity>> entities;
};
