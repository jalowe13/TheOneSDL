#pragma once
#include "Application.h"



Application::Application()
{
	std::cout << "Application Created!\n";
	gameRunning = true;
	frameCount = 0;
	startTime = GetTickCount();
	endTime = GetTickCount();
	timeDifference = 0;
	frameAverage = 0;
}

Application::~Application()
{
	std::cout << "Application Destroyed!\n";
}

bool Application::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "SDL Init Done" << std::endl;
			window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			
			if (!window)
			{
				throw "Window creation failed.";
			}
			
			std::cout << "Window created" << std::endl;

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED); //Create renderer
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set clear color to white

			if (!renderer)
			{
				throw "Renderer creation failed.";
			}
			
			std::cout << "Renderer created" << std::endl;

			if (TTF_Init() != 0)
			{
				throw "TTF Init failed.";
			}
			
			std::cout << "TTF Init Done" << std::endl;

			//Loading texture memory
			SDL_Texture* temp_tex = NULL;

			//Create Player
			temp_tex = IMG_LoadTexture(renderer, "VGB_Idle.png");
			player = new Player(temp_tex);
			
			if (!player)
			{
				throw "Player allocation failed.";
			}

			//Create Texture loader
			texLoader = new TextureLoader();
			if (!texLoader)
			{
				throw "Texture Loader creation failed.";
			}
			
			std::cout << "Texture Loader created." << std::endl;

			//Texture Loading
			ground = IMG_LoadTexture(renderer, "textures/floor.bmp");
			if (ground == nullptr)
			{
				std::cout << "Ground Texture Not Loaded!" << std::endl;
			}
			
			terrain_gen = new Terrain(renderer);

			std::cout << "Terrain gen created" << std::endl;
			std::cout << "-----Starting Terrain Generation-----" << std::endl;
			
			
			terrain_gen->fillScreen();
			//terrain_gen->generateText("The One", 64, 64, 4);

			gameRunning = true;
			free(texLoader);
		}
		else
		{
			gameRunning = false;
		}
		
		return true;
	}
	catch(const char* error)
	{
		std::cout << error << std::endl;
		return false;
	}
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
			player->yPathEdit(Up);
			break;
		}
		case SDLK_a:
		{
			player->xPathEdit(Left);
			break;
		}
		case SDLK_s:
		{
			player->yPathEdit(Down);
			break;
		}
		case SDLK_d:
		{
			player->xPathEdit(Right);
			break;
		}
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
		{
			player->yPathEdit(None);
			break;
		}
		case SDLK_a:
		{
			player->xPathEdit(None);
			break;
		}
		case SDLK_s:
		{
			player->yPathEdit(None);
			break;
		}
		case SDLK_d:
		{
			player->xPathEdit(None);
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
	player->updateTexture();
	player->handleMovement();
}

void Application::render()
{
	SDL_RenderClear(renderer); //Clear Screen
	//Terrain
	for (int i = 0; i < terrain_gen->getTerrainSize(); i++)
	{
		SDL_RenderCopy(renderer, terrain_gen->getText(i), NULL, terrain_gen->getTerrain(i));
	}
	for (int i = 0; i < terrain_gen->getTextSize(); i++)
	{
		SDL_RenderCopy(renderer, terrain_gen->getText(i), NULL, terrain_gen->getTextRec(i));
	}
	//Player
	SDL_RenderCopy(renderer, player->getTexture(), player->getRectTex(), player->getRect());
	//Show Frame
	SDL_RenderPresent(renderer);
}

void Application::clean()
{
	delete player; // Destroy player memory
	delete terrain_gen;
	SDL_DestroyWindow(window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
	TTF_Quit(); //Deletee all TTF text
}








