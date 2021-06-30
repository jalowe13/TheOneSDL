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
			std::cout << "SDL Init Done\n";
			window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (window)
			{
				std::cout << "Window created\n";
			}

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED); //Create renderer
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Set clear color to white

			if (renderer)
			{
				std::cout << "Renderer created\n";
			}

			if (TTF_Init() == 0)
			{
				std::cout << "TTF Init Done \n";
			}

			//Loading texture memory
			SDL_Texture* temp_tex = NULL;

			//Create Player
			temp_tex = IMG_LoadTexture(renderer, "VGB_Idle.png");
			player = new Player(temp_tex);

			//Create Texture loader
			texLoader = new TextureLoader();
			if (texLoader != NULL)
			{
				std::cout << "Texture Loader created\n";
			}

			createText("Testing", 0, 0);
			//createTexture("X",0, 0);

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
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, player->getTexture(), player->getRectTex(), player->getRect());
	SDL_RenderCopy(renderer, titleTexture, NULL, titleRect);
	SDL_RenderPresent(renderer);
}

void Application::clean()
{
	delete player; // Destroy player memory
	SDL_DestroyWindow(window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
	TTF_Quit(); //Deletee all TTF text
}

void Application::createText(const char* text, float x, float y)
{
	//Create Text
//Create Font
	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
	//Create Color
	SDL_Color color = { 255, 0, 0 };
	//Surface for Text
	SDL_Surface* surface = TTF_RenderText_Solid(font,
		text, color);
	//Render Surface to Texture
	titleTexture = SDL_CreateTextureFromSurface(renderer, surface);

	//Create rectangle location
	titleRect = new SDL_Rect();
	titleRect->x = x;
	titleRect->y = y;
	titleRect->w = 200;
	titleRect->h = 200;


	//Free Font
	TTF_CloseFont(font);
}

void Application::createTexture(const char* filename, float x, float y)
{
	//Create Text
//Create Font
	TTF_Font* font = TTF_OpenFont("arial.ttf", 25);
	//Create Color
	SDL_Color color = { 255, 255, 255 };
	//Surface for Text
	SDL_Surface* surface = TTF_RenderText_Solid(font,
		filename, color);
	//Render Surface to Texture
	titleTexture = SDL_CreateTextureFromSurface(renderer, surface);

	//Create rectangle location
	titleRect = new SDL_Rect();
	titleRect->x = 32;
	titleRect->y = 32;
	titleRect->w = 100;
	titleRect->h = 100;


	//Free Font
	TTF_CloseFont(font);
}







