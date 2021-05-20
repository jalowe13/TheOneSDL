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

	currentDirectionX = None;
	currentDirectionY = None;

	destR.h = 16;
	destR.w = 16;
	destR.x = 1;
	destR.y = 1;

	srcR.h = 32;
	srcR.w = 32;
	srcR.x = 100;
	srcR.y = 100;
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

	player = IMG_LoadTexture(renderer,"player.bmp");
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
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) 
		{
		case SDLK_w:
		{
			std::cout << "Up\n";
			currentDirectionY = Up;
			break;
		}
		case SDLK_a:
		{
			std::cout << "Left\n";
			currentDirectionX = Left;
			break;
		}
		case SDLK_s:
		{
			std::cout << "Down\n";
			currentDirectionY = Down;
			break;
		}
		case SDLK_d:
		{
			std::cout << "Right\n";
			currentDirectionX = Right;
			break;
		}
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		{
			std::cout << "Up Release\n";
			currentDirectionY = None;
			break;
		}
		case SDLK_a:
		{
			std::cout << "Left Release\n";
			currentDirectionX = None;
			break;
		}
		case SDLK_s:
		{
			std::cout << "Down Release\n";
			currentDirectionY = None;
			break;
		}
		case SDLK_d:
		{
			std::cout << "Right Release\n";
			currentDirectionX = None;
			break;
		}
		}
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
	//endTime = GetTickCount();
	//timeDifference = endTime - startTime;
	//frameCount++;
	//frameAverage = frameCount / timeDifference;
	//std::cout << frameCount << ":" << timeDifference << std::endl;
	//std::cout << "[" << destR.x << "," << destR.y << "]\n";
	
	if (boundsCheck(destR.x, destR.y))
	{
		switch (currentDirectionX)
		{
			case Left:
			{
				destR.x--;
				break;
			}
			case Right:
			{
				destR.x++;
				break;
			}
			}
		switch (currentDirectionY)
		{
			case Up:
			{
				destR.y--;
				break;
			}
			case Down:
			{
				destR.y++;
				break;
			}
		}
	}
	else if (!boundsCheck(destR.x, destR.y))
	{
		std::cout << destR.x << "," << destR.y << std::endl;
		switch (currentDirectionX)
		{
		case Right:
		{
			destR.x--;; //Fix violation in direction
			break;
		}
		case Left:
		{
			destR.x++; //Fix violation in direction
			break;
		}
		}
		switch (currentDirectionY)
		{
		case Down:
		{
			destR.y--; //Fix violation in direction
			break;
		}
		case Up:
		{
			destR.y = destR.y++;//Fix violation in direction
			break;
		}
		}
		if (destR.x >= SCREEN_WIDTH)
		{
			destR.x = destR.x - 5;
		}
		if (destR.y >= SCREEN_HEIGHT)
		{
			destR.y = destR.y - 5;
		}
		if (destR.x <= 0)
		{
			destR.x = destR.x + 5;
		}
		if (destR.y <= 0)
		{
			destR.y = destR.y + 5;
		}
	}
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

bool Application::boundsCheck(int x, int y)
{
	if (x > 0 && y > 0)
	{
		if ((x < SCREEN_WIDTH) && (y < SCREEN_HEIGHT))
		{
			return true;
		}
	}
	return false;
}


