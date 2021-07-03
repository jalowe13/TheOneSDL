#include "terrain.h"


Terrain::Terrain(SDL_Renderer* renderer_p)
{
	renderer = renderer_p;
	std::cout << "Terrain Generation Started" << std::endl;
	std::cout << "Terrain List Size " << terrainListSize << std::endl;
	std::cout << "Terrain List Capacity " << terrainListCapacity << std::endl;
}

Terrain::~Terrain()
{
	std::cout << "Terrain Deconstructed" << std::endl;
}

SDL_Texture* Terrain::generateTerrain(const char* name, int x, int y)
{
	//Create Text
//Create Font
	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
	//Create Color
	SDL_Color color = { 255, 0, 0 };
	//Surface for Text
	SDL_Surface* surface = TTF_RenderText_Solid(font,
		name, color);
	//Create rectangle location
	SDL_Rect* new_rect = new SDL_Rect();
	setTerrain(new_rect);
	SDL_Rect* currentRect = getTerrain(getTerrainSize());
	currentRect->x = x;
	currentRect->y = y;
	currentRect->w = 32;
	currentRect->h = 32;


	//std::cout << "Rect created at " << terrainList[terrainListSize]->x << "," << terrainList[terrainListSize]->y << std::endl;
	incSize();
	//std::cout << getTerrainSize() << std::endl;

	//Free Font
	TTF_CloseFont(font);

	return SDL_CreateTextureFromSurface(renderer, surface); //Returns texture
}

void Terrain::renderTerrain()
{
	
}

SDL_Texture* Terrain::fillScreen(const char* name)
{
	int x = 0;
	int y = 0;
	SDL_Texture* textureFilled;
	// 26 max blocks in X Direction for a Y in 800*600
	for (int i = 0; i < terrainListCapacity; i++)
	{
			textureFilled = generateTerrain(name, x, y);
			if (x < SCREEN_WIDTH)
			{
				x = x + 32;
			}
			else if (x >= SCREEN_WIDTH)
			{
				x = 0;
				y = y + 32;
			}
	}
	std::cout << "Fill complete, blocks created ["
		<< terrainListSize << "]" << std::endl;
	return textureFilled;
}


