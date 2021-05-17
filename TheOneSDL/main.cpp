#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Application.h"
#include <iostream>

//Pointers NULL
Application* app = NULL; //Pointer to the app

//Create new SDL interface window
bool initializeWindow()
{
	app = new Application(); //Create new Application
	//Create SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) //If SDL could not start
	{
		std::cout << "SDL could not initialize! SDL_Error: %s\n";
		return false;
	}
	else //Window can be created
	{
		app->window = SDL_CreateWindow(app->windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->SCREEN_WIDTH, app->SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //Window to create
		if (app->window == NULL)
		{
			std::cout << "The Window could not be created! \n";
			return false; // Return in error
		}
	}
	return true;
}

int main(int argc, char* args[])
{
	SDL_SetMainReady(); //Ready SDL
	initializeWindow(); //Create new window

	app->surface = SDL_GetWindowSurface(app->window); // Set surface
	SDL_FillRect(app->surface, NULL, SDL_MapRGB(app->surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(app->window); //update
	char c;
	std::cout << "Hello World! \n";
	std::cin >> c;
	SDL_DestroyWindow(app->window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
	return 0;
}