#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Player.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#ifndef APPLICATION_HPP
#define APPLICATION_HPP


class Application
{
public:
	Application();
	~Application();

	//Windows and Surfaces
	SDL_Window* getWindow();
	SDL_Surface* getSurface();
	SDL_Renderer* getRenderer();
	const int getScreenWidth();
	const int getScreenHeight();
	void setWindow(SDL_Window* new_window);
	void setSurface(SDL_Surface* new_surface);
	void setRenderer(SDL_Renderer* new_renderer);

	//Events
	void init();
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();


	//Constants for reference
	const char* windowTitle = "The One SDL v.0.6.0 FPS:";

	const int fps = 144;
private:

	//Pointers
	SDL_Window* window = NULL; //Pointer to Window
	SDL_Renderer* renderer = NULL; //Render graphics
	SDL_Surface* surface = NULL; //Pointer to Surface in Window
	SDL_Surface* sf_background = NULL; //Background pointer

	SDL_Surface* surface_temp = NULL;
	SDL_Texture* titleTexture = NULL;
	SDL_Texture* player_texture = NULL;


	Player* player = NULL;


	

	//Game Variables
	bool gameRunning;
	int frameCount;
	int startTime;
	int endTime;
	int timeDifference;
	float frameAverage;
	

};

#endif