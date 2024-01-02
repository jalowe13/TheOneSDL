#pragma once

#include "Entity.h"
#include <vector>

class EntityManager {
public:
  EntityManager();
  ~EntityManager();
  //   void createEntity();
  void addEntity(std::unique_ptr<Entity> entity);
  //   void destroyEntity(int entityId);
  int getEntityCount();
  const std::vector<std::unique_ptr<Entity>> &getEntities() const;
  // Add your member function declarations here

private:
  std::vector<std::unique_ptr<Entity>> entities;
};
