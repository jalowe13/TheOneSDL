/*
 * EntityManager.cpp
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
#include "EntityManager.h"

EntityManager::EntityManager() {
  // Constructor implementation
  std::cout << "EntityManager Created\n";
  std::cout << "Current size is " << entities.size() << "\n";
}

EntityManager::~EntityManager() {
  // Destructor implementation
  std::cout << "EntityManager Destroyed\n";
}

void EntityManager::createAndAddEntity(SDL_Renderer *renderer,
                                       Entity::EntityType type, int x, int y) {
  std::unique_ptr<Entity> entity;
  switch (type) {
  case Entity::PLAYER_E:
    std::cout << "Creating Player in Entity Manager\n";
    entity = std::make_unique<Player>(renderer, x, y);
    break;
  case Entity::ENEMY_E:
    std::cout << "Creating Enemy in Entity Manager\n";
    entity = std::make_unique<Enemy>(renderer, x, y);
    break;
  default:
    std::cout << "Invalid type\n";
    exit(-1);
    break;
  }
  size_t oldSize = entities.size();
  entities.push_back(std::move(entity));
  if (entities.size() != oldSize + 1) {
    throw "Entity allocation failed.";
  }
  std::cout << "There are now " << entities.size() << " entities\n";
}

void EntityManager::addEntity(std::unique_ptr<Entity> entity) {
  entities.push_back(std::move(entity));
}
std::vector<std::unique_ptr<Entity>> &EntityManager::getEntities() {
  return entities;
}

// void EntityManager::destroyEntity(int entityId) {}

// Entity *EntityManager::getEntity(int entityId) { return nullptr; }

int EntityManager::getEntityCount() { return entities.size(); }
