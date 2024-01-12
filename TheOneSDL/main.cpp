/*
* main.cpp
* Copyright (C) [2024] [Jacob Lowe]
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#include "Application.h"

#include "resource.h" //sounds

#include <string>
// #pragma comment(lib, "winmm.lib")

// Pointers NULL
Application *app = NULL; // Pointer to the app

void framerate_cap(Uint32 frame, const Uint64 fps) {
  if ((1000 / fps) > SDL_GetTicks64() - frame) {
    SDL_Delay(1000 / fps - (SDL_GetTicks64() - frame));
  }
}

int main(int argc, char *args[]) {
  app = new Application();
  app->init();

  Uint32 starting_tick;
  Uint32 fps_update_timer = 0;

  // Application loop
  while (app->running()) {
    Uint64 start_timer = SDL_GetPerformanceCounter(); // Start FPS Clock
    starting_tick = SDL_GetTicks64();                 // Get current clock ticks

    // Game handling events
    app->handleEvents();
    app->update();
    app->render();
    // Cap FPS and Wait timer
    framerate_cap(starting_tick, app->fps);

    Uint64 end_timer = SDL_GetPerformanceCounter(); // End FPS clock after delay
    // Calculate and print framerate
    float elapsed_time =
        (end_timer - start_timer) / (float)SDL_GetPerformanceFrequency();
    // std::string currentFPS =
    // app->windowTitle + std::to_string(1.0f / elapsed_time);
    // SDL_SetWindowTitle(app->getWindow(), currentFPS.c_str());

    app->current_fps = 1.0f / elapsed_time; // pass to application current fps

    // Update frames only every second
    if (SDL_GetTicks64() - fps_update_timer > 1000) {
      std::stringstream ss;
      ss << app->windowTitle << app->current_fps;
      SDL_SetWindowTitle(app->getWindow(), ss.str().c_str());
      fps_update_timer = SDL_GetTicks64();
      std::string currentFPS =
          app->windowTitle + std::to_string(int(1.0f / elapsed_time));
      SDL_SetWindowTitle(app->getWindow(), currentFPS.c_str());
    }
  }
  app->clean();
  delete app;
  return 0;
}
