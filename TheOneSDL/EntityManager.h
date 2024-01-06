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
  void addEntity(std::unique_ptr<Entity> entity);
  //   void destroyEntity(int entityId);
  int getEntityCount();
  const std::vector<std::unique_ptr<Entity>> &getEntities() const;
  // Add your member function declarations here

private:
  std::vector<std::unique_ptr<Entity>> entities;
};
