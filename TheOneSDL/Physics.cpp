#include "Physics.h"

Physics::Physics(){
  std::cout << "Start Physics Engine" << std::endl;
}

Physics::~Physics(){
  std::cout << "Stopping Physics Engine" << std::endl;
}

float Physics::getGravity(){
    return gravity;
}

bool Physics::checkCollision(int x, int y, char obj_tilemap[19][26]){
  //Convert cords to tile
  x = x/32;
  y = (y/32)+1; // This + 1 is to account for a slight skew debug this
  // std::cout << x << "," << y << std::endl;
  // std::cout << obj_tilemap[y][x] << std::endl;
  if(obj_tilemap[y][x] == 'f')
  {
    // std::cout << obj_tilemap[y][x] << std::endl;
    // std::cout << "stop" << std::endl;
    return FALSE;
  }
  // if (x == x){
  //   if(y1 + 1 == y2) // Detect next tile collision
  //   {
  //     std::cout << "stop" << std::endl;
  //     return TRUE;
  //   }
  // }
  return TRUE;
}
