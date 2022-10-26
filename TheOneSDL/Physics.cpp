#include "Physics.h"
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
  std::cout << "Time:" << time << std::endl;
  return time;
}

bool Physics::checkCollision(int x, int y, char obj_tilemap[19][26]){
  //Convert cords to tile
  x = x/32;
  y = (y/32)+1; // This + 1 is to account for a slight skew debug this
  // std::cout << obj_tilemap[y][x] << std::endl;
  if(obj_tilemap[y][x] == 'f')
  {
    return false;
  }
  return true;
}
