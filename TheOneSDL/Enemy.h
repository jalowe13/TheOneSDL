#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

class Terrain;
class Physics;

class Enemy {
public:
  Enemy(SDL_Renderer *default_texture);
  ~Enemy();

  // Getters and Setters
  SDL_Texture *getTexture();
  SDL_Rect *getRect();
  SDL_Rect *getRectTex();

  // Collision and gravity check
  void checkCollision(int i, Physics *phys_eng);

  // Handle movement from the Physics engine
  void handleMovement(Physics *phys_eng, Terrain *terrain_eng);

  void updateTexture(Physics *phys_eng, Terrain *terrain_eng);

  void setTexture(SDL_Texture *texture);

private:
  // temp
  bool left_look = true;

  // Variables
  SDL_Texture *enemy_texture = NULL;
  SDL_Rect enemyR;
  SDL_Rect textureR;
  SDL_Rect playerHitboxR;
  int tilemap_x;
  int tilemap_y;
  bool hitboxOn;
  std::string chomper_idle_left = "textures/enemy/chomper/chompter_idle.png";
  std::string chomper_move_left =
      "textures/enemy/chomper/Chomper_Move-Left.png";
  std::string chomper_move_right =
      "textures/enemy/chomper/Chomper_Move-Right.png";
  // Textures stored
  std::map<std::string, SDL_Texture *> textures;
  int textureWidth, textureHeight, frameWidth, frameHeight, frame_time;
  bool inAnimation = false; // toggle to lock animation canceling
};