#include "SDL.h"

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
	Player();
	~Player();

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


	void handleMovement();
	bool boundsCheck(int x, int y);

	//Texture Edits
	void xTexEdit(int x);
	void yTexEdit(int y);
	void wTexEdit(int w);
	void hTexEdit(int h);
	//Texture Getters
	int getTexX();

	

private:
	SDL_Rect playerR;
	SDL_Rect textureR;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	int movementModifier;


};
#endif