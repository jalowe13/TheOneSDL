#ifndef PHYSICS_HPP
#define PHYSICS_HPP


class Physics
{
public:
	Physics();
	~Physics();
	float getGravity(); // Global Gravity return
	bool checkCollision(int x, int y, char obj_tilemap[19][26]); //Check collision of object and tileset
private:
	const float gravity = 1;

};
#endif
