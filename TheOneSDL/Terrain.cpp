#include "Terrain.h"

// Block
Block::Block()
{
  x = 100;
  y = 100;
  w = 50;
  h = 50;
  centerX = x + w / 2;
  centerY = y + h / 2;
}

Block::Block(int x_i, int y_i)
{
  x = x_i;
  y = y_i;
  w = 32;
  h = 32;
  centerX = x + w / 2;
  centerY = y + h / 2;
}

Block::Block(std::string name_i, int x_i, int y_i, SDL_Texture* texture_i)
{
  x = x_i;
  y = y_i;
  w = 32;
  h = 32;
  centerX = x + w / 2;
  centerY = y + h / 2;
  name = name_i;
  texture = texture_i;
  SDL_Rect new_rect = {x, y, w, h};
  rect = new_rect;
  
//   if (name == "Floor")
//   {
// 	std::cout << name <<" created at " << rect.x << "," << rect.y << std::endl;
//   }
}

void Block::draw(SDL_Renderer* renderer) {
  

  if (texture != NULL)
  {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
  }
  else
  {
	std::cout << "No texture at position" << x << "," << y << std::endl;
	// Generate a random color as a no texture warning
	Uint8 r = rand() % 256;
	Uint8 g = rand() % 256;
	Uint8 b = rand() % 256;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  }
  if (hitboxRender)
  {
	SDL_Rect hitbox = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &hitbox);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  }
}

void Block::print_blockInfo()
{
	std::cout << "~~~~Block: " << name << " ~~~~\n";
	std::cout << "x,y:" << x << "," << y << std::endl;
	std::cout << "center x,y:" << centerX << "," << centerY << std::endl;
}

std::string* Block::getName()
{
	return &name;
}


SDL_Rect* Block::get_Rect()
{
	return &rect;
}
// Terrain functions

Terrain::Terrain(SDL_Renderer* renderer_p)
{
	renderer = renderer_p;
	std::cout << "-----Terrain Generation Started" << std::endl;
	blocks.reserve(10);
}

Terrain::~Terrain()
{
	std::cout << "-----Terrain Deconstructed" << std::endl;
}

void Terrain::generateText(const char* text, int x, int y, int scale)
{
	// SDL TTF Removed
// 	//Create Text
// //Create Font
// 	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
// 	//Create Color
// 	SDL_Color color = { 255, 0, 0 };
// 	//Surface for Text
// 	SDL_Surface* surface = TTF_RenderText_Solid(font,
// 		text, color);
// 	//Create rectangle location
// 	SDL_Rect* new_text = new SDL_Rect();
// 	new_text->x = x;
// 	new_text->y = y;
// 	new_text->w = 32*scale;
// 	new_text->h = 32*scale;

// 	//Free Font
// 	TTF_CloseFont(font);

// 	textList[textListSize] = SDL_CreateTextureFromSurface(renderer, surface); //Returns texture
// 	textListSize++;
}


bool Terrain::fillScreen()
{
	SDL_Texture* textureFilled;
	char tile = '~';
	SDL_Texture* texture = NULL;
	std::string name;
	// 26 max blocks in X Direction for a Y in 800*600 26 20
	for (int layer = 0; layer < 2; layer++) {
		int x = 0;
		int y = 0;
		for (int iy = 0; iy < tilemapY; iy++)
		{
			for (int ix = 0; ix < tilemapX; ix++)
			{
				// Pull each char from the tilemap to translate to textures
				switch (layer) {
				case 0:
					tile = background_tilemap[iy][ix];
					break;
				case 1:
					tile = obj_tilemap[iy][ix];
					break;
				}
				texture = NULL;
				// Identify Texture
				switch (tile) {
				case 'f':
					texture = IMG_LoadTexture(renderer, FLOOR_TEX);
					name = "Floor";
					break;
				case 'g':
					texture = IMG_LoadTexture(renderer, GROUND_TEX);
					name = "Ground";
					break;
				case 'l':
					texture = IMG_LoadTexture(renderer, LAMP_TEX);
					name = "Lamp";
					break;
				case 'p':
					texture = IMG_LoadTexture(renderer, POSTER_TEX);
					name = "Poster";
					break;
				case 't':
					texture = IMG_LoadTexture(renderer, TV_TEX);
					name = "TV";
					break;
				case 'w':
					texture = IMG_LoadTexture(renderer, WALL_TEX);
					name = "Wall";
					break;
				case '1':
					//For the Player, Might not be needed
					break;
				// Temporary Import 
				case 'c':
					texture = IMG_LoadTexture(renderer, CHOMPER_TEX);
					name = "Chomper";
					
					break;
				}
				if (texture != NULL && x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
					//std::cout << x << "," << y << std::endl;
					Block block(name,x,y,texture);
					blocks.push_back(block);
					//std::cout << "Size:" << blocks.size() << std::endl;
					//generateTerrain(texture, x, y, layer);
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
	return true;
}


void Terrain::loadLevel(std::string level)
{
	std::cout << "Load level: " << level << std::endl;
	fillScreen();
}

void Terrain::print_allBlockInfo()
{
	std::cout << "Start\n";
	std::cout << "Blocks" << blocks.size() << std::endl;
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].print_blockInfo();
	}
	std::cout << "End\n";
}

std::vector<Block>* Terrain::getBlockVector()
{
	return &blocks;
}