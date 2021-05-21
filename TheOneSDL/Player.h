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
	
	//Setters
	void xPathEdit(MovementDirection path);
	void yPathEdit(MovementDirection path);
	void xEdit(int x);
	void yEdit(int y);
	void editMS(int speed);

	void handleMovement();
	bool boundsCheck(int x, int y);
	

private:
	SDL_Rect playerR;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	int movementModifier;


};
#endif