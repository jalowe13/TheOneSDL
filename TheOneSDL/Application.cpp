#include "Application.h"

// Upgrade to C++ 11

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
	std::cout << "-----Application Created\n";
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
	std::cout << "-----Application Destroyed\n";
}

bool Application::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "-----SDL Init Done" << std::endl;
			window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (!window)
			{
				throw "Window creation failed.";
			}

			std::cout << "-----Window Created" << std::endl;

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED); //Create renderer
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); //Set clear color to white

			if (!renderer)
			{
				throw "Renderer creation failed.";
			}

			std::cout << "-----Renderer Created" << std::endl;

			//Loading texture memory
			SDL_Texture* temp_tex = NULL;

			//Create Player This needs to be changed to be added in the tilemap
			// renderer is passed in to load the texture
			// If the memory is owned by the class and not shared outside of the class
			// make it a unique ptr. If it is shared outside of the class weak ptr

			// weak ptr.lock
			//designed for shared references

			// raw pointers for viewing  (careful with these!)

			player = new Player(renderer); // make share ptr for different classes
			enemy = new Enemy(renderer);

			if (!player)
			{
				throw "Player allocation failed.";
			}
			if (!enemy)
			{
				throw "Enemy allocation failed.";
			}
			//Create Texture loader

			//Unique make share
			//include memroy.h
			// std::make_unique 

			std::cout << "-----Texture Loader Created" << std::endl;

			//Texture Loading

			terrain_gen = new Terrain(renderer);
			if (!terrain_gen)
			{
				throw "Terrain Generator creation failed.";
			}
			std::cout << "-----Terrain Generator Created" << std::endl;
			std::cout << "-----Starting Terrain Generation" << std::endl;
			terrain_gen->loadLevel("Room");
			std::cout << "-----Terrain Generation Complete" << std::endl;

			// Start Physics engine
			phys_eng = new Physics();

			gameRunning = true;
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

void Application::update() // Update Logic
{
	// Logic first before rendering texture
	// Logic --> Physics --> Render Fix!!
	// Update texture needs to go into render
	player->updateTexture(phys_eng, terrain_gen); // Update players texture
	enemy->updateTexture(phys_eng, terrain_gen); // Update enemy texture
	// This is fine
	player->checkCollision(phys_eng->checkRectCollision(player->getHitboxRect(),terrain_gen),phys_eng); // Check player collision with terrain
	//terrain_gen->fillScreen(); // Update textures and rectangles
}

void Application::render()
{
	SDL_RenderClear(renderer); //Clear Screen
	// Background Textures Rendering and placement

	// Const reference to the block vector
	// Never pass a string by copy

	// C++ Unique Pointers, References and Ownership
	// Look up books from creator of C++
	// Scott Myers Effective C++, More effective C++, One for 11, Tour of C++ 17
	// Rust and GO

	std::vector<Block>* terrain_vector = terrain_gen->getBlockVector();
	for (Block &block : *terrain_vector) // Iterate
	{
		block.draw(renderer);
	}

	// Enemies
	SDL_RenderCopy(renderer, enemy->getTexture(), enemy->getRectTex(), enemy->getRect());
	//Player
	SDL_RenderCopy(renderer, player->getTexture(), player->getRectTex(), player->getRect());
	
	// Hitbox Rendering
	if (player->hitboxCheck())
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, player->getHitboxRect());
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	}

	SDL_RenderPresent(renderer);
}

void Application::clean()
{
	delete player; // Destroy player memory //unique ptr would take care of this
	delete terrain_gen;
	SDL_DestroyWindow(window); //destroy the window
	SDL_Quit(); //quit and delete all SDL
}
