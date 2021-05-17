#pragma once

struct _Application
{
	//Constants

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const char* versionNumber = "v.0.1.0";
	const char* windowTitle = "The One SDL v.0.1.0";

	//Pointers
	SDL_Window* window = NULL; //Pointer to Window
	SDL_Surface* surface = NULL; //Pointer to Surface in Window
	SDL_Surface* sf_background = NULL; //Background pointer
	SDL_Renderer* renderer = NULL; //Render graphics

}; typedef struct _Application Application;