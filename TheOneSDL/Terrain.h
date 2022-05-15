
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
	void generateText(const char* text, int x, int y, int scale);
	bool generateTerrain(SDL_Texture* texture, int x, int y);
	bool fillScreen();


	const static int tilemapY = 19;
	const static int tilemapX = 26;
	char empty_tilemap[tilemapY][tilemapX] = {
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'}
	};
	char tilemap[tilemapY][tilemapX] = {
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','f','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','g','w','w','w','w','w','w','w','w','w','w','w'},
		{'f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f'},
		{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'}
	};
	//Terrain
	const char* GROUND_TEX = "textures/enviroment/room/ground.bmp";
	const char* FLOOR_TEX = "textures/enviroment/room/floor.bmp";
	const char* WALL_TEX = "textures/enviroment/room/wallcenter.bmp";


	void setTerrain(SDL_Rect* rect)
	{
		terrainList[terrainListSize] = rect;
	}

	void setText(SDL_Texture* texture)
	{
		textList[terrainListSize] = texture;
	}

	SDL_Rect* getTerrain(int i)
	{
		return terrainList[i];
	}

	SDL_Texture* getText(int i)
	{
		return textList[i];
	}

	SDL_Rect* getTextRec(int i)
	{
		return textListRec[i];
	}

	int getTextSize()
	{
		return textListSize;
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
	int textListSize = 0;
	static const int terrainListCapacity = 493; //MAX SIZE
	SDL_Rect* terrainList[terrainListCapacity];
	SDL_Texture* textList[terrainListCapacity]; //Storage of text textures
	SDL_Rect* textListRec[20]; //Storage of text
	SDL_Renderer* renderer;
};

#endif