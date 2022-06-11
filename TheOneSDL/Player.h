
#include "Application.h"
#include "Physics.h"
#include "Terrain.h"
#include <iostream>

#ifndef PLAYER_HPP
#define PLAYER_HPP

enum MovementDirection {
	Up,
	Down,
	Left,
	Right,
	None
};

class Player
{
public:
	Player(SDL_Texture* default_texture);
	~Player();

	void updateTexture();

	//Getters
	const int getSpeed();
	MovementDirection xPath();
	MovementDirection yPath();
	int getX();
	int getY();
	int getMS();
	SDL_Rect* getRect();
	SDL_Rect* getRectTex();

	//Setters
	void xPathEdit(MovementDirection path);
	void yPathEdit(MovementDirection path);
	void xEdit(int x);
	void yEdit(int y);
	void wEdit(int w);
	void hEdit(int h);
	void editMS(int speed);
	void handleMovement(Physics* phys_eng, Terrain* terrain_eng);
	bool boundsCheck(int x, int y);
	void setTexture(SDL_Texture* texture);

	//Texture Edits
	void xTexEdit(int x);
	void yTexEdit(int y);
	void wTexEdit(int w);
	void hTexEdit(int h);

	//Texture Getters
	int getTexX();
	SDL_Texture* getTexture();




private:

	//Methods


	//Variables
	SDL_Rect playerR;
	SDL_Rect textureR;

	SDL_Texture* player_texture = NULL;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	int movementModifier;


	int textureWidth, textureHeight, frameWidth, frameHeight;
	std::string texture_name = "VGB_Idle";

	int frame_time;


};
#endif
