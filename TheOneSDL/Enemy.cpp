#include "Enemy.h"

Enemy::Enemy(SDL_Renderer *renderer) {
  // Enemy Rectangle
  // Variables
  enemyR.h = 32;
  enemyR.w = 32;
  tilemap_x = 10;
  tilemap_y = 16;
  enemyR.x = tilemap_x * 32;
  enemyR.y = tilemap_y * 32;

  // Textures and frames
  textureWidth = 0;
  textureHeight = 0;
  frameWidth = textureWidth / 60;
  frameHeight = textureHeight;
  frame_time = 0;

  std::cout << "Loading Enemy Textures...\n";

  const char *filename; // Filename to load
  SDL_Texture *texture; // Default texture pointer
  std::list<std::string> tex_files = {chomper_idle_left, chomper_move_left,
                                      chomper_move_right};
  std::list<std::string> tex_names = {"chomper_idle_left", "chomper_move_left",
                                      "chomper_move_right"};

  while (tex_files.size() > 0) {
    std::string new_file = tex_files.front().c_str(); // Reference from front
    filename = new_file.c_str();
    std::string name = tex_names.front();
    tex_names.pop_front(); // pop
    tex_files.pop_front();
    texture = IMG_LoadTexture(renderer, filename);
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    textures[name] = texture;
    // std::cout << "Enemy.cpp: Texture loaded " << name << " with path:" <<
    // filename << " with dims " << textureWidth << " and " << textureHeight <<
    // std::endl;
    if (textures[name] == 0 || textureWidth == 0 || textureHeight == 0) {
      std::cout << name << " failed to load from path " << filename
                << std::endl;
      exit(-1);
    }
  }

  std::cout << "-----Enemy Created\n";
}

Enemy::~Enemy() { std::cout << "-----Enemy Destroyed\n"; }

void Enemy::handleMovement(Physics *phys_eng, Terrain *terrain_eng) {
  if (!inAnimation) {
    if (left_look) {
      setTexture(textures["chomper_move_left"]);
    } else {
      setTexture(textures["chomper_move_right"]);
    }
    inAnimation = true;
  }
}

// Same as player class
void Enemy::updateTexture(Physics *phys_eng, Terrain *terrain_eng) {
  textureR.x = textureR.x + frameWidth;
  if (textureR.x >= textureWidth) // Reset back to the end of the texture
  {
    textureR.x = 0;
  }
  if (frame_time >
      60) // Unknown why this frametime feature exists, investigate further
  {
    inAnimation = false;
    if (left_look) {
      left_look = false;
    } else {
      left_look = true;
    }
    frame_time = 0;
  } else {
    handleMovement(phys_eng, terrain_eng);
    frame_time++;
  }
}
void Enemy::setTexture(SDL_Texture *texture) {
  enemy_texture = texture;
  SDL_QueryTexture(enemy_texture, NULL, NULL, &textureWidth, &textureHeight);
  frameWidth = textureWidth / 60;
  frameHeight = textureHeight;
  textureR.x = 0;
  textureR.y = 0;
  textureR.w = frameWidth;
  textureR.h = frameHeight;
}

SDL_Texture *Enemy::getTexture() { return enemy_texture; }

SDL_Rect *Enemy::getRect() { return &enemyR; }

SDL_Rect *Enemy::getRectTex() { return &textureR; }