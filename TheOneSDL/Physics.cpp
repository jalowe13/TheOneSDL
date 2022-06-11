#include "Physics.h"

Physics::Physics(){
  std::cout << "Start Physics Engine" << std::endl;
}

Physics::~Physics(){
  std::cout << "Stopping Physics Engine" << std::endl;
}

int Physics::getGravity(){
    return gravity;
}

bool Physics::checkCollision(int x, int y, char obj_tilemap[19][26]){
  //Convert cords to tile
  y = y/20;
  std::cout << x << "," << y << std::endl;

  if(obj_tilemap[x][y] == 'f')
  {
    std::cout << obj_tilemap[x][y] << std::endl;
    std::cout << "stop" << std::endl;
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
