#define SDL_MAIN_HANDLED
#pragma once
#include <iostream>
#include <windows.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "SDL.h"
#include "Player.h"
#include "TextureLoader.h"
#include "terrain.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#ifndef APPLICATION_HPP
#define APPLICATION_HPP


class Application
{
public:
	Application();
	~Application();

	//Windows and Surfaces
	SDL_Window* getWindow()
	{
		return window;
	}
	SDL_Surface* getSurface()
	{
		return surface;
	}
	SDL_Renderer* getRenderer()
	{
		return renderer;
	}
	const int getScreenWidth()
	{
		return SCREEN_WIDTH;
	}
	const int getScreenHeight()
	{
		return SCREEN_HEIGHT;
	}
	void setWindow(SDL_Window* new_window)
	{
		window = new_window;
	}
	void setSurface(SDL_Surface* new_surface)
	{
		surface = new_surface;
	}
	void setRenderer(SDL_Renderer* new_renderer)
	{
		renderer = new_renderer;
	}

	//Events
	bool init();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running()
	{
		return gameRunning;
	}

	//Getters
	//Player* getPlayer();

	//Text Events
	void createText(const char* text, float x, float y);
	void createTexture(const char* filename, float x, float y);


	//Constants for reference
	const char* windowTitle = "C23 Engine: The One SDL v.0.6.0 FPS:";

	int textureWidth = 1920;
	int textureHeight = 32;
	int frameWidth, frameHeight;

	const int fps = 60;
	int current_fps= 0;
	int frame_time = 0;
private:

	//Pointers
	SDL_Window* window = NULL; //Pointer to Window
	SDL_Renderer* renderer = NULL; //Render graphics
	SDL_Surface* surface = NULL; //Pointer to Surface in Window
	SDL_Surface* sf_background = NULL; //Background pointer
	SDL_Surface* surface_temp = NULL;

	//Rectangles
	SDL_Rect* titleRect; //Title Location rectangle

	//Rectangle List
	int terrainListSize = 0;
	static const int terrainListCapacity = 493; //MAX SIZE
	SDL_Rect* terrainList[terrainListCapacity];

	//Textures
	SDL_Texture* titleTexture = NULL;


	
	Player* player = NULL;
	TextureLoader* texLoader = NULL;


	

	//Game Variables
	bool gameRunning;
	int frameCount;
	int startTime;
	int endTime;
	int timeDifference;
	float frameAverage;
	

};

#endif