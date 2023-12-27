#include "Application.h"

#include "resource.h" //sounds

#include <string>
// #pragma comment(lib, "winmm.lib")



//Pointers NULL
Application* app = NULL; //Pointer to the app



void framerate_cap(Uint32 frame, const Uint64 fps)
{
	if ((1000 / fps) > SDL_GetTicks64() - frame)
	{
		SDL_Delay(1000 / fps - (SDL_GetTicks64() - frame));
	}
}

int main(int argc, char* args[])
{
	app = new Application();
	app->init();

	Uint32 starting_tick;
	Uint32 fps_update_timer = 0;
	
	//Application loop
	while (app->running())
	{
		Uint64 start_timer = SDL_GetPerformanceCounter(); //Start FPS Clock
		starting_tick = SDL_GetTicks64(); //Get current clock ticks

		//Game handling events
		app->handleEvents();
		app->update();
		app->render();
		//Cap FPS and Wait timer
		framerate_cap(starting_tick, app->fps);

		Uint64 end_timer = SDL_GetPerformanceCounter(); //End FPS clock after delay
		//Calculate and print framerate
		float elapsed_time = (end_timer - start_timer) / (float)SDL_GetPerformanceFrequency();
		std::string currentFPS = app->windowTitle + std::to_string(1.0f / elapsed_time);
		SDL_SetWindowTitle(app->getWindow(),currentFPS.c_str());

		app->current_fps = 1.0f / elapsed_time; // pass to application current fps

		// Update frames only every second
		if (SDL_GetTicks64() - fps_update_timer > 1000) {
        std::stringstream ss;
        ss << app->windowTitle << app->current_fps;
        SDL_SetWindowTitle(app->getWindow(), ss.str().c_str());
        fps_update_timer = SDL_GetTicks64();
		}
	}
	app->clean();
	delete app;
	return 0;
}