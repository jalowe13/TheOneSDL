#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <deque>
#include <tuple>
#include <map>
#include <regex>
#include <iostream>
#include <vector>
#include "Application.h"

// Block to be rendered by the terrain
class Block {
public:
    // Default block placement
    Block();
    // Block placement with cord params
    Block(int x_i, int y_i);
    // Block placement with cord and texture
    Block(std::string name, int x_i, int y_i, SDL_Texture* texture_i);
	// Draw the current block in the renderer
    void draw(SDL_Renderer* renderer);

	int getX() {return x;}
	int getY() {return y;}

    // Get the center of the block.
    int getCenterX() { return x + w / 2; }
    int getCenterY() { return y + h / 2; }

	// Get block info
	void print_blockInfo();
	// Get block name
	std::string* getName();
	// Get block rectangle
	SDL_Rect* get_Rect();


	std::string name;

    private:
    int x, y, w, h, centerX, centerY;
    SDL_Texture* texture = NULL;
    
	SDL_Rect rect;
	//Debugging
	bool hitboxRender = false;
};

class Terrain
{
public:
	Terrain(SDL_Renderer* renderer_p);
	~Terrain();
	void generateText(const char* text, int x, int y, int scale);



	// Iterates through all tilemaps, and loads textures into a texture array
	// Texture arrays are updated
	// Rectangle arrays are updated
	bool fillScreen();

	// Print all contents of all blocks
	void print_allBlockInfo();
	// Block Vector getter
	std::vector<Block>* getBlockVector();

	// Array Max sizes 800x600
	const static int tilemapY = 19;
	const static int tilemapX = 26;

	// Texture height and width in pixels
	const static int texBounds = 32;

	// Empty Tilemap template
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

	char background_tilemap[tilemapY][tilemapX] = {
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
	};

	// Object interactable tilemap
	// JSON Format?
	char obj_tilemap[tilemapY][tilemapX] = {
		{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','f','f','f','~','~','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~','~','f','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~','~','~','f','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','f','f','f','~','~','~','~','~','~','~','~','~','~'},
		{'~','~','~','f','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~','~','~','~','~','f','~'},
		{'~','~','~','~','~','~','~','~','~','f','f','~','~','f','~','~','~','~','~','~','~','~','f','~','~'},
		{'~','~','~','~','~','~','~','~','f','~','~','~','~','~','~','~','~','~','~','~','~','f','~','~','~'},
		{'~','f','~','~','~','~','~','f','f','~','~','~','~','~','~','~','~','p','~','~','f','~','~','~','~'},
		{'~','~','~','~','~','f','f','~','f','~','~','~','~','~','~','~','~','~','~','f','~','~','~','~','~'},
		{'~','~','~','~','~','~','~','~','f','~','~','~','~','l','c','t','~','~','f','~','~','~','~','~','~'},
		{'f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f','f'},
		{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'}
	};
	//Terrain
	const char* GROUND_TEX = "textures/enviroment/room/ground.bmp";
	const char* FLOOR_TEX = "textures/enviroment/room/floor.bmp";
	const char* WALL_TEX = "textures/enviroment/room/wallcenter.bmp";
	//Transparent Textures
	const char* LAMP_TEX = "textures/enviroment/room/lamp.png";
	const char* TV_TEX = "textures/enviroment/room/tv_fix.png";
	const char* POSTER_TEX = "textures/enviroment/room/floyd_poster.png";

	// Temporary Enemy Textures
	const char* CHOMPER_TEX = "textures/enemies/chomper/chomper.png";


	// Terrain Setters and Getters

	// Sets the rectangle in the terrain rectangle list
	void setTerrain(SDL_Rect* rect)
	{
		terrainList[terrainListSize] = rect;
	}

	// Sets the texture in the texture list
	void setText(SDL_Texture* texture)
	{
		textList[terrainListSize] = texture;
	}

	// Storage of Background Objects Rectangles
	SDL_Rect* getTerrain(int i)
	{
		return terrainList[i];
	}
	
	// Get Texture in the Background Texture list
	SDL_Texture* getText(int i)
	{
		return textList[i];
	}

	// Get "text" font, rectangle
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

	// Terrain OBJ Setters and Getters
	void setTerrainObj(SDL_Rect* rect)
	{
		terrainObjList[terrainObjListSize] = rect;
	}

	void setTextObj(SDL_Texture* texture)
	{
		textObjList[terrainObjListSize] = texture;
	}

	// Storage of Terrain Objects Rectangles
	SDL_Rect* getTerrainObj(int i)
	{
		return terrainObjList[i];
	}

	SDL_Texture* getTextObj(int i)
	{
		return textObjList[i];
	}
	int getTerrainObjSize()
	{
		return terrainObjListSize;
	}


private:
	//insertMap(int x, int y);
	//std::map<int,int>* terrain_p; //Terrain Map 25 tile wide for 800 pix
	//Rectangle List
	int terrainListSize = 0;
	int textListSize = 0;
	int terrainObjListSize = 0;
	int textObjListSize = 0;
	static const int terrainListCapacity = 493; //MAX SIZE
	static const int terrainObjListCapacity = 493; //MAX SIZE

	// New Gen
	std::vector<Block> blocks;

	// Old Gen

	// Background Terrain
	SDL_Rect* terrainList[terrainListCapacity]; //Storage of Background textures
	SDL_Texture* textList[terrainListCapacity]; //Storage of text textures

	// Terrain Objects
	SDL_Rect* terrainObjList[terrainObjListCapacity]; // Storage of Terrain Objects
	SDL_Texture* textObjList[terrainObjListCapacity]; //Storage of text textures

	// Text
	SDL_Rect* textListRec[20]; //Storage of text
	// Renderer
	SDL_Renderer* renderer;
};

#endif
