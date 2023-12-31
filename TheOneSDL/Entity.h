// Entity.h
#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Player;
class Enemy;

class Entity {
public:
  enum MovementDirection {
    Up,
    Down,
    Left,
    Right,
    None
  };                                             // Movement Direction of
  enum LookingDirection { LookRight, LookLeft }; // Looking Direction of
protected:
  SDL_Rect rect;
  SDL_Texture *texture;
  MovementDirection currentDirectionX;
  MovementDirection currentDirectionY;
  float movementModifier;
  bool hitboxOn;
  // ... any other common properties

public:
  Entity(SDL_Renderer *renderer); // constructor
  virtual ~Entity();              // destructor

  // Common methods
  const float getSpeed();
  MovementDirection xPath();
  MovementDirection yPath();
  int getX();
  int getY();
  SDL_Texture *getTexture();
  SDL_Rect *getRect();
  bool hitboxCheck();
  SDL_Rect *getHitboxRect();
  void xPathEdit(MovementDirection path);
  void yPathEdit(MovementDirection path);
  // ... any other common methods
};

#endif