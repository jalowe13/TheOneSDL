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
		else
		{
			app->surface = SDL_GetWindowSurface(app->window); // Set surface
		}
	}
	return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	app->sf_background = SDL_LoadBMP("woods.bmp");
	if (app->sf_background == NULL)
	{
		std::cout << "Unable to load image\n";
		success = false;
	}
	else
	{
		std::cout << "Loaded!\n";
		SDL_BlitSurface(app->sf_background, NULL, app->surface, NULL);
	}

	return success;
}

int main(int argc, char* args[])
{
	SDL_SetMainReady(); //Ready SDL
	initializeWindow(); //Create new window
	//Create Renderer
	app->renderer = SDL_CreateRenderer(app->window, -1, 0);
	//Create Surface
	loadMedia(); //Add image
	SDL_UpdateWindowSurface(app->window);

	//SDL_ShowWindow(app->window);

	char c;
	std::cout << "Application running, enter anything to exit \n";
	std::cin >> c;
	SDL_DestroyWindow(app->window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
	return 0;
}