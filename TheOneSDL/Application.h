#define SDL_MAIN_HANDLED
#include "SDL.h"

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

	const char* windowTitle = "The One SDL v.0.3.0";
	const char* versionNumber = "v.0.1.0";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
private:

	//Pointers
	SDL_Window* window = NULL; //Pointer to Window
	SDL_Renderer* renderer = NULL; //Render graphics
	SDL_Surface* surface = NULL; //Pointer to Surface in Window
	SDL_Surface* sf_background = NULL; //Background pointer

	//Game Variables

};

#endif