#include "Application.h"
#include <iostream>
#include <windows.h>
#include "SDL_image.h"



Application::Application()
{
	std::cout << "Application Created!\n";
	gameRunning = true;
	frameCount = 0;
	startTime = GetTickCount();
	endTime = GetTickCount();
	timeDifference = 0;
	frameAverage = 0;


	surface_temp = SDL_LoadBMP("woods.bmp");
	player = SDL_CreateTextureFromSurface(renderer, surface_temp);
	SDL_FreeSurface(surface_temp);
}

Application::~Application()
{
	std::cout << "Application Destroyed!\n";
}

SDL_Window* Application::getWindow()
{
	return window;
}

SDL_Surface* Application::getSurface()
{
	return surface;
}

SDL_Renderer* Application::getRenderer()
{
	return renderer;
}

const int Application::getScreenWidth()
{
	return SCREEN_WIDTH;
}

const int Application::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

void Application::setWindow(SDL_Window* new_window)
{
	window = new_window;
}

void Application::setSurface(SDL_Surface* new_surface)
{
	surface = new_surface;
}

void Application::setRenderer(SDL_Renderer* new_renderer)
{
	renderer = new_renderer;
}

void Application::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL Init Done\n";
		window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window)
		{
			std::cout << "Window created\n";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			std::cout << "Renderer created\n";
		}
		gameRunning = true;

	}
	else
	{
		gameRunning = false;
	}

	player = IMG_LoadTexture(renderer,"woods.bmp");
}

void Application::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	default:
		break;
	}
}

void Application::update()
{
	//startTime = GetTickCount();
	//endTime = GetTickCount();
	//frameCount = startTime - endTime;
	endTime = GetTickCount();
	timeDifference = endTime - startTime;
	frameCount++;
	frameAverage = frameCount / timeDifference;
	std::cout << frameCount << ":" << timeDifference << std::endl;
	
	destR.h = 32;
	destR.w = 32;
}

void Application::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, player, NULL, &destR);
	SDL_RenderPresent(renderer);
}

void Application::clean()
{
	SDL_DestroyWindow(window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
}

bool Application::running()
{
	return gameRunning;
}


