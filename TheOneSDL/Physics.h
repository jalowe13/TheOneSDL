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
	const float gravity = 0.98;
	const float timeI = .05;
	const float jumpForgiveness = 0; // Skew for landing on top of a tile: Higher will forgive more
	float time = 0.0;

};
#endif
