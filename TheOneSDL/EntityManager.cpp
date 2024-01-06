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
    entity = std::make_unique<Player>(renderer, x, y);
    break;
  case Entity::ENEMY_E:
    entity = std::make_unique<Enemy>(renderer, x, y);
    break;
  default:
    std::cout << "Invalid type\n";
    exit(-1);
    break;
  }
  entities.push_back(std::move(entity));
}

void EntityManager::addEntity(std::unique_ptr<Entity> entity) {
  entities.push_back(std::move(entity));
}
const std::vector<std::unique_ptr<Entity>> &EntityManager::getEntities() const {
  return entities;
}

// void EntityManager::destroyEntity(int entityId) {}

// Entity *EntityManager::getEntity(int entityId) { return nullptr; }

int EntityManager::getEntityCount() { return entities.size(); }
