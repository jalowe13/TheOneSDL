#ifndef PLAYER_HPP
#define PLAYER_HPP


#include "Terrain.h"
#include <SDL2/SDL_ttf.h>

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

	//Setters
	void xPathEdit(MovementDirection path);
	void yPathEdit(MovementDirection path);
	void xEdit(int x);
	void yEdit(int y);
	void wEdit(int w);
	void hEdit(int h);
	void editMS(float speed);
	void handleMovement(Physics* phys_eng, Terrain* terrain_eng, bool animation);
	bool boundsCheck(int x, int y);
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




private:

	//Methods


	//Variables
	SDL_Rect playerR;
	SDL_Rect textureR;

	int tilemap_x;
	int tilemap_y;

	SDL_Texture* player_texture = NULL;

	MovementDirection currentDirectionX = None;
	MovementDirection currentDirectionY = None;
	float movementModifier;


	int textureWidth, textureHeight, frameWidth, frameHeight;
	//std::string texture_name = "VGB_Idle";
	std::string idle_file = "textures\\VGB\\idle\\vgb_idle-Sheet.png";
	std::string idle_file2 = "VGB_Idle.png";

	std::string run_left_file = "textures\\VGB\\run\\vgb_run_left-Sheet.png";

	//Textures stored
	SDL_Texture* texture = NULL;
	SDL_Texture* texture2 = NULL;
	SDL_Texture* run_left = NULL;

	int frame_time;
	bool inAnimation = false; // toggle to lock animation canceling


};
#endif
