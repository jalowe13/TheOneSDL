#pragma once

#include "Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Player : public Entity {
  // Add player-specific members and functions here
public:
  Player(SDL_Renderer *renderer, int x,
         int y); // Declare the constructor // Constructor
  ~Player();     // Destructor
  void handleMovement(Physics *phys_eng, Terrain *terrain_eng) override;
  std::list<std::string> getTexturePaths(); // Texture file paths
  std::list<std::string> getTextureNames(); // Texture file names
private:
  // Texture Paths
  std::string idle_left = "textures/VGB/idle/vgb_idle-left-Sheet.png";
  std::string idle_right = "textures/VGB/idle/vgb_idle-right-Sheet.png";
  std::string run_left = "textures/VGB/run/vgb_run_left-Sheet.png";
  std::string run_right = "textures/VGB/run/vgb_run_right-Sheet.png";
  std::string sit = "textures/VGB/idle/vgb_gamer_idle-Sheet.png";
  // Texture Data Structures
  std::list<std::string> tex_files = {idle_left, idle_right, run_left,
                                      run_right, sit};
  std::list<std::string> tex_names = {"idle_left", "idle_right", "run_left",
                                      "run_right", "sit"};
};
