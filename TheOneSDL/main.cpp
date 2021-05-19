#include "Application.h"
#include <windows.h>
#include "resource.h" //sounds
#include <iostream>
#pragma comment(lib, "winmm.lib")



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
		app->setWindow(SDL_CreateWindow(app->windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			app->SCREEN_WIDTH, app->SCREEN_HEIGHT, SDL_WINDOW_SHOWN)); //Window to create
		if (app->getWindow() == NULL)
		{
			std::cout << "The Window could not be created! \n";
			return false; // Return in error
		}
		else
		{
			app->setSurface(SDL_GetWindowSurface(app->getWindow())); // Set surface
		}
	}
	return true;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	SDL_Surface* background = SDL_LoadBMP("woods.bmp");
	if (background == NULL)
	{
		std::cout << "Unable to load image\n";
		success = false;
	}
	else
	{
		std::cout << "Loaded!\n";
		SDL_BlitSurface(background, NULL, app->getSurface(), NULL);
	}

	return success;
}

int main(int argc, char* args[])
{
	SDL_SetMainReady(); //Ready SDL
	initializeWindow(); //Create new window
	//Create Renderer
	app->setRenderer(SDL_CreateRenderer(app->getWindow(), -1, 0));
	//Create Surface
	loadMedia(); //Add image
	SDL_UpdateWindowSurface(app->getWindow());

	//SDL_ShowWindow(app->window);

	bool soundPlayed = PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE); //Play title music
	if (!soundPlayed)
	{
		std::cout << "Sound was unable to be played.\n";
	}
	else
	{
		std::cout << "Sound was played\n";
	}
	

	char c;
	std::cout << "Application running, enter anything to exit \n";
	std::cin >> c;
	SDL_DestroyWindow(app->getWindow()); //destroy the window
	SDL_Quit(); //quit and delete all SDL
	return 0;
}