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
  int y_tile = int((y/Terrain::texBounds))+1; // This + 1 is to account for tilemap skew: must fix in rendering
  if(obj_tilemap[y_tile][x_tile] == 'f' ) // Floor specifics
  {
    // Need to check for top of the floor around ~20 pixels
    int a_y = int((y-jumpForgiveness)/Terrain::texBounds)+1;
    if(obj_tilemap[a_y][x_tile] == '~')
    {
      return false; // Player is on the ground
    }
  }
  return true; // Player is not on the ground
}
