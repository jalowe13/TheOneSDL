#include "Application.h"
#include <windows.h>
#include "resource.h" //sounds
#include <iostream>
#pragma comment(lib, "winmm.lib")



//Pointers NULL
Application* app = NULL; //Pointer to the app




int main(int argc, char* args[])
{
	char c;
	std::cout << "Application running, enter anything to exit \n";

	app = new Application();
	app->init();
	
	//Application loop
	while (app->running())
	{
		app->handleEvents();
		app->update();
		app->render();
	}
	app->clean();
	delete app;
	return 0;
}