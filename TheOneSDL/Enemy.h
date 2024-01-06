#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Enemy : public Entity {
  // Add Enemy-specific members and functions here
public:
  Enemy(SDL_Renderer *renderer, int x,
        int y); // Declare the constructor // Constructor
  ~Enemy();     // Destructor
  std::list<std::string> getTexturePaths(); // Texture file paths
  std::list<std::string> getTextureNames(); // Texture file names
private:
  // Texture Paths
  std::string chomper_idle_left = "textures/enemy/chomper/chompter_idle.png";
  std::string chomper_move_left =
      "textures/enemy/chomper/Chomper_Move-Left.png";
  std::string chomper_move_right =
      "textures/enemy/chomper/Chomper_Move-Right.png";
  // Texture Data Structures
  std::list<std::string> tex_files = {chomper_idle_left, chomper_move_left,
                                      chomper_move_right};
  std::list<std::string> tex_names = {"chomper_idle_left", "chomper_move_left",
                                      "chomper_move_right", "run_right", "sit"};
};