#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Terrain.h"

class Terrain;
class Physics;

class Enemy
{
    public:
    	Enemy(SDL_Renderer* default_texture);
	    ~Enemy();

		// Getters and Setters
		SDL_Texture* getTexture();
		SDL_Rect* getRect();
		SDL_Rect* getRectTex();
		// Handle movement from the Physics engine 
		void handleMovement(Physics* phys_eng, Terrain* terrain_eng);

	    void updateTexture(Physics* phys_eng, Terrain* terrain_eng);

		void setTexture(SDL_Texture* texture);


    private:
	//Variables
	SDL_Texture* enemy_texture = NULL;
	SDL_Rect enemyR;
	SDL_Rect textureR;
	SDL_Rect playerHitboxR;
	int tilemap_x;
	int tilemap_y;
	bool hitboxOn;
	std::string chomper_idle_left = "textures/VGB/idle/vgb_gamer_idle-Sheet.png";
	//Textures stored
	std::map<std::string, SDL_Texture*> textures;
	int textureWidth, textureHeight, frameWidth, frameHeight, frame_time;
	bool inAnimation = false; // toggle to lock animation canceling
};
#endif