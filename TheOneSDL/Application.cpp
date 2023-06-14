#include "Application.h"

#ifdef _WIN32
#else
uint32_t linux_tick(){
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
}
#endif

Application::Application()
{
	std::cout << "Application Created!\n";
	gameRunning = true;
	frameCount = 0;
	// Windows and Linux Definitions
	#ifdef _WIN32
		startTime = GetTickCount();
		endTime = GetTickCount();
	#else
		startTime = linux_tick();
		endTime = linux_tick();
	#endif
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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Set clear color to white

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
			// renderer is passed in to load the texture
			player = new Player(renderer);

			if (!player)
			{
				throw "Player allocation failed.";
			}
			std::cout << "Player created\n";

			//Create Texture loader
			texLoader = new TextureLoader();
			if (!texLoader)
			{
				throw "Texture Loader creation failed.";
			}

			std::cout << "Texture Loader created." << std::endl;

			//Texture Loading

			terrain_gen = new Terrain(renderer);

			std::cout << "Terrain gen created" << std::endl;
			std::cout << "-----Starting Terrain Generation-----" << std::endl;


			terrain_gen->fillScreen();
			terrain_gen->print_allBlockInfo();
			//terrain_gen->generateText("The One", 64, 64, 4);

			// Start Physics engine
			phys_eng = new Physics();

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
			player->editMS(3);
			break;
		}
		case SDLK_a:
		{
			player->xPathEdit(Left);
			player->editMS(2);
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
			player->editMS(2);
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
	player->updateTexture(phys_eng, terrain_gen); // Update players texture
	//terrain_gen->fillScreen(); // Update textures and rectangles
	// std::cout << "update\n";
}

void Application::render()
{
	SDL_RenderClear(renderer); //Clear Screen
	// Background Textures Rendering and placement
	if (true) // Toggle to test background rendering versus object rendering
	{
		for (int i = 0; i < terrain_gen->getTerrainSize(); i++)
		{
			SDL_RenderCopy(renderer, terrain_gen->getText(i), NULL, terrain_gen->getTerrain(i));
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			SDL_RenderDrawRect(renderer, terrain_gen->getTerrain(i));
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
	}
	// // Object Rendering and placement
	if (true)
	{
		for (int i = 0; i < terrain_gen->getTerrainObjSize(); i++)
		{
			SDL_RenderCopy(renderer, terrain_gen->getTextObj(i), NULL, terrain_gen->getTerrainObj(i));
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(renderer, terrain_gen->getTerrainObj(i));
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}
	}
	// //Player
	SDL_RenderCopy(renderer, player->getTexture(), player->getRectTex(), player->getRect());
	// Hitbox Rendering
	if (player->hitboxCheck())
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, player->getHitboxRect());
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	}
	// // Declare block
	// Block block(500,500);
	// // Draw the block.
	// block.draw(renderer);
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
