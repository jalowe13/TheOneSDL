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



bool Physics::checkCollision(int x, int y, char obj_tilemap[19][26]){
  //Convert cords to tile
  int x_tile = int(x/Terrain::texBounds);
  int y_tile = int((y/Terrain::texBounds)); // This + 1 is to account for tilemap skew: must fix in rendering
  //std::cout << "ytile:" << y_tile << std::endl;
  //std::cout << obj_tilemap[y_tile][x_tile] << std::endl;
  //std::cout << obj_tilemap[y_tile+1][x_tile] << std::endl;
  if(obj_tilemap[y_tile+1][x_tile] == 'f' || obj_tilemap[y_tile][x_tile] == 'f' ) // Collision
  {
    if(obj_tilemap[y_tile][x_tile] == 'f')
    {
      std::cout << "error in floor\n";
    }
    return false;
  }
  return true; // Player is not on the ground, keep falling
}
