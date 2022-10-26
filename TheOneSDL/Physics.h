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
	float getGravity(); // Global Gravity return
	bool checkCollision(int x, int y, char obj_tilemap[19][26]); //Check collision of object and tileset
	void incTime(); //Start a float timer
	void resetTime(); //End and reset float timer
	float getTime(); //Get the amount of time
private:
	const float gravity = 0.98;
	const float timeI = .05;
	float time = 0.0;

};
#endif
