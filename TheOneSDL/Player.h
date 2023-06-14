#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "Terrain.h"
#include <SDL2/SDL_ttf.h>
#include <list>
#include <vector>

class Terrain;
class Physics;

enum MovementDirection {
	Up,
	Down,
	Left,
	Right,
	None
};

class Player
{
public:
	Player(SDL_Renderer* default_texture);
	~Player();

	void updateTexture(Physics* phys_eng, Terrain* terrain_eng);

	//Getters
	const float getSpeed();
	MovementDirection xPath();
	MovementDirection yPath();
	int getX();
	int getY();
	float getMS();
	SDL_Rect* getRect();
	SDL_Rect* getRectTex();
	// Return Player Hitbox Rectangle
	SDL_Rect* getHitboxRect();

	//Setters
	void xPathEdit(MovementDirection path);
	void yPathEdit(MovementDirection path);
	void xEdit(int x);
	void yEdit(int y);
	void wEdit(int w);
	void hEdit(int h);
	void editMS(float speed);
	// Handle movement from the Physics engine 
	void handleMovement(Physics* phys_eng, Terrain* terrain_eng);
	// Check if Player is outside of the screen
	bool boundsCheck(int x, int y);
	//Setting Textures to the passed in texture
	void setTexture(SDL_Texture* texture);
	void set_tilemap_pos(int x, int y);

	//Texture Edits
	void xTexEdit(int x);
	void yTexEdit(int y);
	void wTexEdit(int w);
	void hTexEdit(int h);

	//Texture Getters
	int getTexX();
	SDL_Texture* getTexture();

	//Hitbox Methods
	bool hitboxCheck();




private:

	//Methods


	//Variables
	SDL_Rect playerR;
	SDL_Rect textureR;
	SDL_Rect playerHitboxR;
	bool hitboxOn;

	int tilemap_x;
	int tilemap_y;

	//Speed
	int playerSpeed;

	// Movemment Status
	bool playerFalling;

	SDL_Texture* player_texture = NULL;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	float movementModifier;


	int textureWidth, textureHeight, frameWidth, frameHeight;

	// Filenames
	std::string idle = "textures/VGB/idle/vgb_idle-Sheet.png";
	std::string run_left = "textures/VGB/run/vgb_run_left-Sheet.png";
	std::string run_right = "textures/VGB/run/vgb_run_right-Sheet.png";
	std::list<std::string> tex_files;

	//Textures stored
	std::map<std::string, SDL_Texture*> textures;


	int frame_time;
	bool inAnimation = false; // toggle to lock animation canceling


};
#endif
