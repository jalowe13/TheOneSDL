#pragma once
#include "Physics.h"
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Terrain;
class Physics;

class Entity {
public:
  enum EntityType { Player, Enemy, Projectile };
  enum MovementDirection {
    Up,
    Down,
    Left,
    Right,
    None
  };                                             // Movement Direction of
  enum LookingDirection { LookRight, LookLeft }; // Looking Direction of
  Entity(SDL_Renderer *renderer, int x, int y, EntityType type); // Constructor
  ~Entity();
  // Entity Factory
  std::unique_ptr<Entity> createEntity(SDL_Renderer *renderer, int x, int y,
                                       Entity::EntityType type);

  void updateTexture(Physics *phys_eng, Terrain *terrain_eng);

  // Getters
  const float getSpeed();
  MovementDirection xPath();
  MovementDirection yPath();
  int getX();
  int getY();
  float getMS();
  SDL_Rect *getRect();
  SDL_Rect *getRectTex();
  // Return Entity Hitbox Rectangle
  SDL_Rect *getHitboxRect();

  // Setters
  void xPathEdit(MovementDirection path);
  void yPathEdit(MovementDirection path);
  void xEdit(int x);
  void yEdit(int y);
  void wEdit(int w);
  void hEdit(int h);
  void editMS(float speed);
  // Passing in char from Physics engine to check collision
  void checkCollision(int i, Physics *phys_eng);
  // Handle movement from the Physics engine
  void handleMovement(Physics *phys_eng, Terrain *terrain_eng);
  // Check if Entity is outside of the screen
  bool boundsCheck(int x, int y);
  // Setting Textures to the passed in texture
  void setTexture(SDL_Texture *texture);
  void set_tilemap_pos(int x, int y);

  // Texture Edits
  void xTexEdit(int x);
  void yTexEdit(int y);
  void wTexEdit(int w);
  void hTexEdit(int h);

  // Texture Getters
  int getTexX();
  SDL_Texture *getTexture();

  // Hitbox Methods
  bool hitboxCheck();

  // Is Colliding
  bool isColliding = false;

private:
  // Methods

  // Variables
  SDL_Rect entityR;
  SDL_Rect textureR;
  SDL_Rect entityHitboxR;
  bool hitboxOn;

  int tilemap_x;
  int tilemap_y;

  // Speed
  int entitySpeed;

  // Looking Status
  LookingDirection looking = LookRight;

  // Movemment Status
  bool entityFalling;

  SDL_Texture *entity_texture = NULL;

  MovementDirection currentDirectionX = None;
  MovementDirection currentDirectionY = None;
  float movementModifier;

  int textureWidth, textureHeight, frameWidth, frameHeight;

  // Filenames
  std::string idle_left = "textures/VGB/idle/vgb_idle-left-Sheet.png";
  std::string idle_right = "textures/VGB/idle/vgb_idle-right-Sheet.png";
  std::string run_left = "textures/VGB/run/vgb_run_left-Sheet.png";
  std::string run_right = "textures/VGB/run/vgb_run_right-Sheet.png";
  std::string sit = "textures/VGB/idle/vgb_gamer_idle-Sheet.png";
  std::list<std::string> tex_files;

  // Textures stored
  std::map<std::string, SDL_Texture *> textures;

  int frame_time;
  bool inAnimation = false; // toggle to lock animation canceling
};