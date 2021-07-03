
#include <deque>
#include <tuple>
#include <map>
#include "Application.h"

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain
{
public:
	Terrain(SDL_Renderer* renderer_p);
	~Terrain();
	SDL_Texture* generateText(const char* text, int x, int y);
	bool generateTerrain(SDL_Texture* texture, int x, int y);
	bool fillScreen(SDL_Texture* texture);
	//Terrain

	void incSize()
	{
		terrainListSize++;
	}

	void setTerrain(SDL_Rect* rect)
	{
		terrainList[terrainListSize] = rect;
	}

	SDL_Rect* getTerrain(int i)
	{
		return terrainList[i];
	}

	int getTerrainSize()
	{
		return terrainListSize;
	}
	int getTerrainCap()
	{
		return terrainListCapacity;
	}

private:
	//insertMap(int x, int y);
	//std::map<int,int>* terrain_p; //Terrain Map 25 tile wide for 800 pix
	//Rectangle List
	int terrainListSize = 0;
	static const int terrainListCapacity = 493; //MAX SIZE
	SDL_Rect* terrainList[terrainListCapacity];
	SDL_Renderer* renderer;
};

#endif