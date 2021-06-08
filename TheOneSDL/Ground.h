#pragma once
#include "SDL.h"

#ifndef GROUND_HPP
#define GROUND_HPP

class Ground
{
public:
	Ground();
	~Ground();
	int getX();
	int getY();

private:
	SDL_Rect groundR;
	//SDL_Texture* groundTexture = IMG_LoadTexture(app.getRenderer(), "ground.bmp");
};

#endif