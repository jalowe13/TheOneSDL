#include "Terrain.h"


Terrain::Terrain(SDL_Renderer* renderer_p)
{
	renderer = renderer_p;
	std::cout << "Terrain Generation Started" << std::endl;
	std::cout << "Terrain List Capacity " << terrainListCapacity << std::endl;
}

Terrain::~Terrain()
{
	std::cout << "Terrain Deconstructed" << std::endl;
}

void Terrain::generateText(const char* text, int x, int y, int scale)
{
	//Create Text
//Create Font
	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
	//Create Color
	SDL_Color color = { 255, 0, 0 };
	//Surface for Text
	SDL_Surface* surface = TTF_RenderText_Solid(font,
		text, color);
	//Create rectangle location
	SDL_Rect* new_text = new SDL_Rect();
	new_text->x = x;
	new_text->y = y;
	new_text->w = 32*scale;
	new_text->h = 32*scale;



	//std::cout << "Text created at " << textListRec[textListSize]->x << "," << textListRec[textListSize]->y << std::endl;

	//std::cout << getTerrainSize() << std::endl;

	//Free Font
	TTF_CloseFont(font);

	textList[textListSize] = SDL_CreateTextureFromSurface(renderer, surface); //Returns texture
	textListSize++;
}

//Sets each rectangle to its position in the array and its corresponding texture
bool Terrain::generateTerrain(SDL_Texture* texture, int x, int y, int layer)
{
	try
	{
		
		SDL_Rect* new_rect = new SDL_Rect();
		SDL_Rect* currentRect = NULL;
		switch (layer){
			case 0:
				setTerrain(new_rect);
				setText(texture);
				currentRect = getTerrain(getTerrainSize());
				currentRect->x = x;
				currentRect->y = y;
				currentRect->w = 32;
				currentRect->h = 32;
				terrainListSize++;
				break;
			case 1:
				setTerrainObj(new_rect);
				setTextObj(texture);
				currentRect = getTerrainObj(getTerrainObjSize());
				currentRect->x = x; // Added for the skew of hitboxes
				currentRect->y = y;
				currentRect->w = 32;
				currentRect->h = 32;
				terrainObjListSize++;
				break;
		}
		return true;
	}
	catch (const char* error)
	{
		std::cout << error << std::endl;
	}
	return false;
}

bool Terrain::fillScreen()
{

	SDL_Texture* textureFilled;
	char tile = '~';
	SDL_Texture* texture = NULL;
	// 26 max blocks in X Direction for a Y in 800*600 26 20
	for (int layer = 0; layer < 2; layer++) {
		int x = 0;
		int y = 0;
		for (int iy = 0; iy < tilemapY; iy++)
		{
			for (int ix = 0; ix < tilemapX; ix++)
			{
				switch (layer) {
				case 0:
					tile = background_tilemap[iy][ix];
					break;
				case 1:
					tile = obj_tilemap[iy][ix];
					break;
				}
				texture = NULL;
				switch (tile) {
				case 'f':
					texture = IMG_LoadTexture(renderer, FLOOR_TEX);
					break;
				case 'g':
					texture = IMG_LoadTexture(renderer, GROUND_TEX);
					break;
				case 'l':
					texture = IMG_LoadTexture(renderer, LAMP_TEX);
					break;
				case 'p':
					texture = IMG_LoadTexture(renderer, POSTER_TEX);
					break;
				case 't':
					texture = IMG_LoadTexture(renderer, TV_TEX);
					break;
				case 'w':
					texture = IMG_LoadTexture(renderer, WALL_TEX);
					break;
				case '1':
					//For the Player, Might not be needed
					//std::cout << "Pxy" << ix << "," << iy << std::endl;
					break;
				}
				if (texture != NULL) {
					std::cout << "x,y:["<< x << "," << y << "]\n";
					generateTerrain(texture, x, y, layer);
				}
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
		}
	}

	// std::cout << "Fill complete, blocks created ["
	// 	<< terrainListSize << "]" << std::endl;
	return true;
}
