
#include "Ground.h"
#include <deque>
#include <tuple>
#include <map>

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain
{
public:
	void generateTerrain();
	void renderTerrain();
	void placeTile(int x, int y);
	void fillScreen();
private:
	//insertMap(int x, int y);
	//std::map<int,int>* terrain_p; //Terrain Map 25 tile wide for 800 pix
};

#endif