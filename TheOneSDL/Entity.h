#pragma once
#include "Physics.h"
#include <cmath>    // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep
#include <list>
#include <map>
#include <memory> // IWYU pragma: keep
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Terrain;
class Physics;

class Entity {
public:
  enum EntityType { NONE, PLAYER_E, ENEMY_E };
  enum MovementDirection {
    Up,
    Down,
    Left,
    Right,
    None
  };                                             // Movement Direction of
  enum LookingDirection { LookRight, LookLeft }; // Looking Direction of
  Entity(SDL_Renderer *renderer, int x, int y);  // Constructor
  ~Entity();

  void loadTextures(SDL_Renderer *renderer);

  void updateTexture(Physics *phys_eng, Terrain *terrain_eng);

  // Getters
  const float getSpeed();
  MovementDirection xPath();
  MovementDirection yPath();
  int getX();
  int getY();
  int getTileX();
  int getTileY();
  float getMS();
  SDL_Rect *getRect();
  SDL_Rect *getRectTex();
  // Return Entity Hitbox Rectangle
  SDL_Rect *getHitboxRect();

  // Setters
  bool &hitBoxToggle();
  void xPathEdit(MovementDirection path);
  void yPathEdit(MovementDirection path);
  void xEdit(int x);
  void yEdit(int y);
  void wEdit(int w);
  void hEdit(int h);
  void editMS(float speed);

  void toggleDirection(); // Toggle Direction of Entity
  // Passing in char from Physics engine to check collision
  void checkCollision(int i, Physics *phys_eng);
  // Handle movement from the Physics engine
  virtual void handleMovement(Physics *phys_eng, Terrain *terrain_eng);
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
  virtual bool hitboxCheck();

  // Is Colliding
  bool isColliding = false;

protected: // Protected so that Player and Enemy can access
  // Textures stored
  std::list<std::string> tex_files;
  std::list<std::string> tex_names;
  std::map<std::string, SDL_Texture *> textures;
  // Type of Entity
  EntityType entityType = NONE; // Default to NONE
                                // Looking Status
  LookingDirection looking = LookRight;
  bool inAnimation = false; // toggle to lock animation canceling
  int tilemap_x;
  int tilemap_y;
  // Movemment Status
  bool entityFalling;
  // Rectangles and Hitbox
  SDL_Rect entityHitboxR;
  SDL_Rect entityR;
  bool hitboxOn;

private:
  // Methods

  // Variables
  SDL_Rect textureR;

  // Speed
  int entitySpeed;

  SDL_Texture *entity_texture = NULL;

  MovementDirection currentDirectionX = None;
  MovementDirection currentDirectionY = None;
  float movementModifier;

  int textureWidth, textureHeight, frameWidth, frameHeight;

  // Filenames
  // std::string idle_left = "textures/VGB/idle/vgb_idle-left-Sheet.png";
  // std::string idle_right = "textures/VGB/idle/vgb_idle-right-Sheet.png";
  // std::string run_left = "textures/VGB/run/vgb_run_left-Sheet.png";
  // std::string run_right = "textures/VGB/run/vgb_run_right-Sheet.png";
  // std::string sit = "textures/VGB/idle/vgb_gamer_idle-Sheet.png";

  int frame_time;
};
