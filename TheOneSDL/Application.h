/*
* Application.h
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
#pragma once

// Version Number
#define VERSION_MAJOR 0
#define VERSION_MINOR 41
#define VERSION_PATCH .1
#define STR_HELPER(x) #x // convert to fit window title
#define STR(x) STR_HELPER(x)

// Screen Definitions

// External Libraries
#include "imgui.h"
#include "imgui_impl_sdl2.h"         // IWYU pragma: keep
#include "imgui_impl_sdlrenderer2.h" // IWYU pragma: keep
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>  // IWYU pragma: keep
#include <iostream> // IWYU pragma: keep
#include <json/json.h>

// PreProcessor Declerations
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>

#endif

// Forward declarations for internal classes
class Enemy;
class Entity;
class EntityManager;
class Physics;
class Terrain;

// Include internal headers after forward declarations
#include "Constants.h"
#include "Enemy.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Physics.h"
#include "Terrain.h"

class Application {
public:
  const char *windowTitle =
      "C23 Engine: The One SDL v" STR(VERSION_MAJOR) "." STR(VERSION_MINOR)
          STR(VERSION_PATCH) " FPS:";
  const char *Title =
      "The One v" STR(VERSION_MAJOR) "." STR(VERSION_MINOR) STR(VERSION_PATCH);
  Application();
  ~Application();

  // Windows and Surfaces
  SDL_Window *getWindow() { return window; }
  SDL_Surface *getSurface() { return surface; }
  SDL_Renderer *getRenderer() { return renderer; }
  const int getScreenWidth() { return SCREEN_WIDTH; }
  const int getScreenHeight() { return SCREEN_HEIGHT; }
  const int getXMouse() { return xMouse; }
  const int getYMouse() { return yMouse; }
  void setWindow(SDL_Window *new_window) { window = new_window; }
  void setSurface(SDL_Surface *new_surface) { surface = new_surface; }
  void setRenderer(SDL_Renderer *new_renderer) { renderer = new_renderer; }

  // Events
  bool init();
  void handleEvents();
  void update();
  void render();
  void clean();
  bool running() { return gameRunning; }

  // Getters
  // Player* getPlayer();

  // Text Events
  void createText(const char *text, int x, int y);
  void createTexture(const char *filename, float x, float y);
  // Constants for reference

  bool debugMode = false;

  int textureWidth = 1920;
  int textureHeight = 32;
  int frameWidth, frameHeight;

  Uint64 fps = 60;
  Uint64 current_fps = 0;
  Uint64 frame_time = 0;

private:
  // Functions
  // Update the Entities
  void updateEntities();
  // Render ImGui Single Frame
  void renderImGuiFrame();
  // Render the ImGui Debug Menu
  void renderDebugMenu();
  // Render Blocks and Entities
  void renderBlockEntities();
  // Pointers
  SDL_Window *window = NULL;         // Pointer to Window
  SDL_Renderer *renderer = NULL;     // Render graphics
  SDL_Surface *surface = NULL;       // Pointer to Surface in Window
  SDL_Surface *sf_background = NULL; // Background pointer
  SDL_Surface *surface_temp = NULL;

  Terrain *terrain_gen = nullptr; // Terrain Generation

  // Mouse
  bool mouseDown;
  int xMouse, yMouse;

  // ImGui
  ImGuiIO io;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Rectangles
  SDL_Rect *titleRect; // Title Location rectangle

  // Physics Engine
  Physics *phys_eng = nullptr; // Pointer to Physics Engine

  // Textures
  SDL_Texture *ground = nullptr;
  SDL_Texture *air = nullptr;

  SDL_Texture *fancy_text = nullptr;

  // Temporary pointers for enemy and player instantiation
  std::unique_ptr<EntityManager> entityManager = NULL;
  std::unique_ptr<Entity> player = NULL;
  Enemy *enemy = NULL;

  // Game Variables
  bool mainMenu;
  bool gameRunning;
  int frameCount;
  int startTime;
  int endTime;
  int timeDifference;
  float frameAverage;
};
