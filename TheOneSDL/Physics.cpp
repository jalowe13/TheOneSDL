#include "Physics.h"
#include "Terrain.h"
#include <iostream>


const std::string Physics::floor = "Floor";

Physics::Physics(){
  std::cout << "Start Physics Engine\n";
  
  std::cout << "Physics Engine Started\n";
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

void Physics::draw(SDL_Renderer *renderer)
{
  //std::cout << "Draw Phys\n";
}

int Physics::checkRectCollision(SDL_Rect* A, Terrain* terrain)
{
  std::vector<Block>* blocks = terrain->getBlockVector();

  for (Block block : *blocks)                     // Iterate through every block
	{
    if (SDL_HasIntersection(A, block.get_Rect())) // Check if its intersecting with another hitbox
    {
      if(floor == block.name)                     // If on Floor return Code for on top of block
      {
        get4Points(A,block.getCenterX(),block.getCenterY());
        return 1;
      }
    }
	}
  return 0;
}

char Physics::get4Points(SDL_Rect* A, int centerX, int centerY)
{
  // A points
  float A_centerX, A_centerY;
  A_centerX = A->x + A->w / 2;
  A_centerY = A->y + A->h / 2;
  //std::cout << "[" << A_centerX << "," << A_centerY << "]\n";

  // B Points of interest 
  float B_NorthX, B_NorthY;
  float B_SouthX, B_SouthY;
  float B_EastX, B_EastY;
  float B_WestX, B_WestY;


}

