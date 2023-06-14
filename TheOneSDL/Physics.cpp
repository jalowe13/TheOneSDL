#include "Physics.h"
#include "Terrain.h"
#include <iostream>

Physics::Physics(){
  std::cout << "Start Physics Engine" << std::endl;
}

Physics::~Physics(){
  std::cout << "Stopping Physics Engine" << std::endl;
}

float Physics::getGravity(){
    return gravity;
}

void Physics::incTime(){
  time = time + (timeI*2);
}

void Physics::resetTime(){
  time = 0.0;
}

float Physics::getTime(){
  return time;
}

int Physics::checkRectCollision(SDL_Rect* A, Terrain* terrain)
{
  std::vector<Block>* blocks = terrain->getBlockVector();

  for (Block block : *blocks) // Iterate
	{
    if (SDL_HasIntersection(A, block.get_Rect()))
    {
      std::string floor = "Floor";
      if(floor == block.name)
      {
        return 1;
      }
    }
	}
  return 0;
}
