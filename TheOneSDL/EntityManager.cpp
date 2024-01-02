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

// void EntityManager::createEntity() {}

void EntityManager::addEntity(std::unique_ptr<Entity> entity) {
  entities.push_back(std::move(entity));
}
const std::vector<std::unique_ptr<Entity>> &EntityManager::getEntities() const {
  return entities;
}

// void EntityManager::destroyEntity(int entityId) {}

// Entity *EntityManager::getEntity(int entityId) { return nullptr; }

int EntityManager::getEntityCount() { return entities.size(); }
