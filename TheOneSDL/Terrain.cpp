/*
* Terrain.cpp
* Copyright (C) [2024] [Jacob Lowe]
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#include "Terrain.h"

// Block
Block::Block() {
  x = 100;
  y = 100;
  w = 50;
  h = 50;
  centerX = x + w / 2;
  centerY = y + h / 2;
}

Block::Block(int x_i, int y_i) {
  x = x_i;
  y = y_i;
  w = 32;
  h = 32;
  centerX = x + w / 2;
  centerY = y + h / 2;
}

Block::Block(std::string name_i, int x_i, int y_i, SDL_Texture *texture_i) {
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
}

void Block::draw(SDL_Renderer *renderer) {

  if (texture != NULL) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
  } else {
    std::cout << "No texture at position" << x << "," << y << std::endl;
    // Generate a random color as a no texture warning
    Uint8 r = rand() % 256;
    Uint8 g = rand() % 256;
    Uint8 b = rand() % 256;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  }
  if (hitboxRender) {
    SDL_Rect hitbox = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &hitbox);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  }
}

void Block::print_blockInfo() {
  std::cout << "~~~~Block: " << name << " ~~~~\n";
  std::cout << "x,y:" << x << "," << y << std::endl;
  std::cout << "center x,y:" << centerX << "," << centerY << std::endl;
}

std::string *Block::getName() { return &name; }

SDL_Rect *Block::get_Rect() { return &rect; }
// Terrain functions

Terrain::Terrain(SDL_Renderer *renderer_p) {
  renderer = renderer_p;
  std::cout << "-----Terrain Generation Started" << std::endl;
  blocks.reserve(10);
}

Terrain::~Terrain() { std::cout << "-----Terrain Deconstructed" << std::endl; }

void Terrain::generateText(const char *text, int x, int y, int scale) {
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

  // 	textList[textListSize] = SDL_CreateTextureFromSurface(renderer,
  // surface); //Returns texture 	textListSize++;
}

bool Terrain::fillScreen() {
  char tile = '~';
  SDL_Texture *texture = NULL;
  std::string name;
  blocks.clear(); // Reset block collisions
  // 26 max blocks in X Direction for a Y in 800*600 26 20
  for (int layer = 0; layer < 2; layer++) {
    int x = 0;
    int y = 0;
    for (int iy = 0; iy < tilemapY; iy++) {
      for (int ix = 0; ix < tilemapX; ix++) {
        // Pull each char from the tilemap to translate to textures
        switch (layer) {
        case 0:
          tile = background_tilemap[iy][ix];
          // std::cout << "fill screen y:" << iy << " x:" << ix << "with: " <<
          // tile << std::endl;
          break;
        case 1:
          tile = obj_tilemap[iy][ix];
          // std::cout << "fill screen y:" << iy << " x:" << ix << "with: " <<
          // tile << std::endl;
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
          // For the Player, Might not be needed
          break;
        // Temporary Import
        case 'c':
          texture = IMG_LoadTexture(renderer, CHOMPER_TEX);
          name = "Chomper";
          break;
        }
        if (texture != NULL && x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
          // std::cout << x << "," << y << std::endl;
          Block block(name, x, y, texture);
          blocks.push_back(block);
          // std::cout << "Size:" << blocks.size() << std::endl;
          // generateTerrain(texture, x, y, layer);
        }
        if (x < SCREEN_WIDTH) {
          x = x + 32;
        } else if (x >= SCREEN_WIDTH) {
          x = 0;
          y = y + 32;
        }
      }
    }
  }
  return true;
}

void Terrain::loadLevel(std::string level) {
  std::ifstream ifs("levels.json"); // JSON file to open
  Json::Value lvl_data; // Map of other JSON values can returna value type,
                        // null, int etc...
  Json::Reader reader;

  if (!reader.parse(ifs, lvl_data)) // If not parsable
  {
    std::cout << "!!!!!Error Parsing Level Data for Level " << level
              << std::endl;
  }

  if (!lvl_data.isObject()) {
    // std::cout << "!!!!Error Parsing: Level data is not object \n";
  }

  if (!lvl_data.isArray()) {
    std::cout << "!!!!Error Parsing: Level Data is not an Array\n";
  }

  for (int i = 0; i < static_cast<int>(lvl_data.size());
       i++) // Iterate through level data
  {
    std::string level_name = lvl_data[i]["name"].asString(); // Grab level name
    if (level_name == level) {
      std::cout << "Load: " << level_name << std::endl;
      for (int map_i = 0; map_i < 2; map_i++) // Load background and tilemap
      {
        switch (map_i) {
        case 0:
          loadTilemap(lvl_data[i]["background_tilemap"], 0);
          break;
        case 1:
          // std::cout << "Start obj\n";
          // std::cout << lvl_data[i] << std::endl;
          loadTilemap(lvl_data[i]["obj_tilemap"], 1);
          break;
        }
      }
    }
  }

  fillScreen();
  // print_allBlockInfo();
}

void Terrain::loadTilemap(Json::Value json_tilemap, int map_type) {
  // Iterators for tilemap
  int tilemapY_i = 0;
  int tilemapX_i = 0;
  if (json_tilemap.size() == 0) {
    std::cout << "Error: Tilemap of type " << map_type << " is size "
              << json_tilemap.size();
  }
  for (int j = 0; j < static_cast<int>(json_tilemap.size()); j++) {
    for (char c : json_tilemap[j].asString()) // Grab new char
    {
      if (tilemapX_i < 24 && tilemapY_i < 20) // Iterate Col
      {
        // The bug is skipping over the iterated char
        switch (map_type) {
        case 0:
          // std::cout << "Replacing " <<
          // background_tilemap[tilemapY_i][tilemapX_i] << " with " << c << " at
          // map " << map_type << std::endl;
          background_tilemap[tilemapY_i][tilemapX_i] = c;
          break;
        case 1:
          // std::cout << "[Replacing " << obj_tilemap[tilemapY_i][tilemapX_i]
          // << " with " << c << " at map " << map_type << std::endl;
          obj_tilemap[tilemapY_i][tilemapX_i] = c;
          // std::cout << "Replacing at " << tilemapY_i << "," << tilemapX_i <<
          // "]" << std::endl;
          break;
        }
        tilemapX_i++;
      } else {
        tilemapX_i = 0;
        if (tilemapY_i < tilemapY) // Iterate Row
        {
          tilemapY_i++;
        }
      }
    }
  }
}

void Terrain::print_allBlockInfo() {
  std::cout << "Start\n";
  std::cout << "Blocks" << blocks.size() << std::endl;
  for (std::vector<Block>::size_type i = 0; i < blocks.size(); i++) {
    blocks[i].print_blockInfo();
  }
  std::cout << "End\n";
}

std::vector<Block> *Terrain::getBlockVector() { return &blocks; }
