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
	SDL_Rect* getRect();
	
	//Setters
	void xPathEdit(MovementDirection path);
	void yPathEdit(MovementDirection path);
	void xEdit(int x);
	void yEdit(int y);

	void handleMovement();
	bool boundsCheck(int x, int y);
	

private:
	SDL_Rect playerR;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	const int movementModifier = 5;


};
#endif