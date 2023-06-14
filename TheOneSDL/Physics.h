#ifndef PHYSICS_HPP
#define PHYSICS_HPP


// Forward declare
#include "Terrain.h"
#include "Player.h"
class Terrain;
class Player;

class Physics
{
public:
	Physics();
	~Physics();
	// Global Gravity return
	float getGravity(); 

	/*
	Check Rectangle Collision, extension of SDL2
	Check if A is colliding with something on the tilemap
	Return true if true false if not
	SDL_Rect* A - Rectangle A (Player or entity)
	std::vector<Block>* blocks - Vector of blocks to check

	Returns integer code of kind of collision
	*/
	int checkRectCollision(SDL_Rect* A, Terrain* terrain);


	/*
	Check collision of object and tileset
		x - Current entity calling x
		y - Current entity calling y
		char obj_tilemap[19][26] - current tilemap
	*/
	bool checkCollision(int x, int y, char obj_tilemap[19][26]);
	//Start a float timer 
	void incTime(); 
	//End and reset float timer
	void resetTime(); 
	//Get the amount of time
	float getTime(); 
private:
	const float gravity = 0.90;		// Would be .98 but cannot reach above 2 blocks
	const float timeI = .05;
	const float jumpForgiveness = 0; // Skew for landing on top of a tile: Higher will forgive more
	float time = 0.0;

};
#endif
