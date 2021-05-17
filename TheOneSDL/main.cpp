#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>


int main()
{
	char c; //Input
	SDL_SetMainReady(); //Ready SDL
	std::cout << "Hello World! \n";
	std::cin >> c; 
	return 0;
}