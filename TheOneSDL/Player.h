#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player : public Entity {
  // Add player-specific members and functions here
public:
  Player(SDL_Renderer *renderer, int x, int y); // Constructor
  ~Player();                                    // Destructor
};
