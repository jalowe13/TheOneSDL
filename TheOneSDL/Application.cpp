/*
* Application.cpp
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
#include "Entity.h"
#include "imgui.h"

#ifdef _WIN32
#else
uint32_t linux_tick() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
}
#endif

Application::Application() {
  std::cout << "-----Application Created\n";
  gameRunning = true;
  frameCount = 0;
// Windows and Linux Definitions
#ifdef _WIN32
  startTime = GetTickCount();
  endTime = GetTickCount();
//   setRefreshRate(); // This games physics is tied to the engine fix later on
#else
  startTime = linux_tick();
  endTime = linux_tick();
#endif
  timeDifference = 0;
  frameAverage = 0;
  mainMenu = true;
}

Application::~Application() { std::cout << "-----Application Destroyed\n"; }

// Initialize Game
bool Application::init() {
  try {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
      std::cout << "-----SDL Init Done" << std::endl;
      window = SDL_CreateWindow(
          windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

      if (!window) {
        throw "Window creation failed!";
      }

      std::cout << "-----Window Created" << std::endl;

      renderer =
          SDL_CreateRenderer(window, -1,
                             SDL_RENDERER_PRESENTVSYNC |
                                 SDL_RENDERER_ACCELERATED); // Create renderer
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set clear color to white

      if (!renderer) {
        throw "Renderer creation failed.";
      }

      std::cout << "-----Renderer Created" << std::endl;

      std::cout << "-----Start ImGUI\n";
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      io = ImGui::GetIO();
      io.ConfigFlags |=
          ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
      io.ConfigFlags |=
          ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
      ImGui::StyleColorsDark();
      // Setup Platform/Renderer backends
      ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
      ImGui_ImplSDLRenderer2_Init(renderer);
      std::cout << "-----ImGUI Created" << std::endl;
      // Create Players and Entities
      // Start EntityManger and add an Entity
      entityManager = std::make_unique<EntityManager>();
      if (!entityManager) {
        throw "EntityManager allocation failed.";
      }

      std::cout << "Attempting to create Player...\n";
      entityManager->createAndAddEntity(renderer, Entity::PLAYER_E, 3, 16);
      if (entityManager->getEntityCount() != 1) {
        throw "Player allocation failed.";
      }
      entityManager->createAndAddEntity(renderer, Entity::ENEMY_E, 11, 16);
      entityManager->createAndAddEntity(renderer, Entity::ENEMY_E, 12, 16);
      if (entityManager->getEntityCount() == 0) {
        throw "Entity allocation failed.";
      }
      std::cout << "-----Texture Loader Created" << std::endl;

      // Texture Loading

      terrain_gen = new Terrain(renderer);
      if (!terrain_gen) {
        throw "Terrain Generator creation failed.";
      }
      std::cout << "-----Terrain Generator Created" << std::endl;
      std::cout << "-----Starting Terrain Generation" << std::endl;
      // terrain_gen->loadLevel("Room");
      terrain_gen->fillScreen(this->getWindow());
      std::cout << "-----Terrain Generation Complete" << std::endl;

      // Start Physics engine
      phys_eng = new Physics();
      std::cout << "--------------------------------\n";
      std::cout << "            GAME START\n";
      std::cout << "--------------------------------\n";
      gameRunning = true;
    } else {
      gameRunning = false;
    }

    return true;
  } catch (const char *error) {
    std::cout << error << std::endl;
    return false;
  }
}
// Future refresh rate settings
// void Application::setRefreshRate() {
//   // DEVMODE dm;
//   // dm.dmSize = sizeof(dm);
//   // EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
//   // this->fps = dm.dmDisplayFreequency;
//   // std::cout << "Refresh Rate: " << this->fps << std::endl;
// }

// Handling all keyboard and mouse events for player
void Application::handleEvents() {
  // auto &entity =
  //     entityManager->getEntities()[0]; // This needs to be changed to a
  //     specific
  // ID reference to the player entity
  std::unique_ptr<Entity> *entity = entityManager->getEntities().data() + 0;
  if (debugMode) {
    std::cout << "Player Position [" << (*entity)->getTileX() << ","
              << (*entity)->getTileY() << "]\r";
  }
  SDL_Event event;
  SDL_PollEvent(&event);
  ImGui_ImplSDL2_ProcessEvent(&event);
  switch (event.type) {
  case SDL_MOUSEMOTION:
    SDL_GetMouseState(&xMouse, &yMouse);
    break;
  case SDL_MOUSEBUTTONDOWN:
    mouseDown = true;
    break;
  case SDL_MOUSEBUTTONUP:
    mouseDown = false;
    break;
  case SDL_QUIT:
    gameRunning = false;
    break;
  case SDL_KEYDOWN: {
    float scaleFactorAvg = (scaleFactorX + scaleFactorY) / 2.0f;
    switch (event.key.keysym.sym) {
    case SDLK_w: {
      (*entity)->yPathEdit(Entity::Up);
      // std::cout << scaleFactorAvg << std::endl;
      (*entity)->editMS(3 + scaleFactorAvg - .5);
      break;
    }
    case SDLK_a: {
      (*entity)->xPathEdit(Entity::Left);
      (*entity)->editMS(2 + scaleFactorAvg - .5);
      break;
    }
    case SDLK_s: {
      (*entity)->yPathEdit(Entity::Down);
      break;
    }
    case SDLK_d: {
      (*entity)->xPathEdit(Entity::Right);
      (*entity)->editMS(2 + scaleFactorAvg - .5);
      break;
    }
    }
    break;
  }
  case SDL_KEYUP:
    switch (event.key.keysym.sym) {
    case SDLK_w: {
      (*entity)->yPathEdit(Entity::None);
      break;
    }
    case SDLK_a: {
      (*entity)->xPathEdit(Entity::None);
      break;
    }
    case SDLK_s: {
      (*entity)->yPathEdit(Entity::None);
      break;
    }
    case SDLK_d: {
      (*entity)->xPathEdit(Entity::None);
      break;
    }
    // Debug Mode Toggle
    case SDLK_BACKQUOTE: {
      debugMode = (debugMode) ? false : true;
      std::cout << "Debug Mode: " << debugMode << std::endl;
      break;
    }
    case SDLK_KP_PLUS: {
      if (debugMode && (fps < 150)) {
        fps += 10;
        std::cout << "\nFps is cap is now " << fps << std::endl;
      }
      break;
    }
    case SDLK_KP_MINUS: {
      if (debugMode && (fps > 10)) {
        fps -= 10;
        std::cout << "\nFps is cap is now " << fps << std::endl;
      }
    }
    case SDLK_1: {
      if (debugMode)
        terrain_gen->loadLevel("DefaultLoad", getWindow());
      break;
    }
    case SDLK_2: {
      if (debugMode)
        terrain_gen->loadLevel("Room", getWindow());
      break;
    }
    case SDLK_3: {
      if (debugMode)
        terrain_gen->loadLevel("EmptyFloor", getWindow());
    }
    }
    break;
  default:
    break;
  }
}
// Update Logic each frame
void Application::update() {
  if (!mainMenu) {    // Not in main menu
    updateEntities(); // Loop through entities and update them
  }
  checkResize(); // Check if resize needs to happen if the window changes
}
// Display textures on screen each frame
void Application::render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(
      renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
      (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 1));
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
  // Rendering for different screens (Main menu and game)
  if (!mainMenu) {
    renderBlockEntities(); // Render all blocks and all entities  // Render the
                           // frame
  } else {
    renderImGuiFrame();
  }
  // Debug mode rendering
  if (debugMode) {
    renderDebugMenu();
  }
  ImGui::Render();
  SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                     io.DisplayFramebufferScale.y);
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  SDL_RenderPresent(renderer); // Present rendered frame
}
// Update logic for Entities for checking collisions
void Application::updateEntities() {
  for (std::unique_ptr<Entity> &entity : entityManager->getEntities()) {
    entity->checkCollision(
        phys_eng->checkRectCollision(entity->getHitboxRect(), terrain_gen),
        phys_eng); // Check entity collision with terrain
    phys_eng->checkEntityCollision(entity.get(), entityManager.get());
  }
}

// GUI handling menu rendering and debug menu
void Application::renderImGuiFrame() {
  // Choose what to show on the frame
  if (debugMode) {
    renderDebugMenu();
  } else if (mainMenu) {
    ImGui::SetNextWindowSize(ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    if (ImGui::Begin("Fullscreen Window", nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove)) {
      ImGui::SetCursorPosY((SCREEN_HEIGHT / 2) - 50);
      ImGui::SetCursorPosX((SCREEN_WIDTH / 2) - 80);
      ImGui::Text(Title);
      ImGui::NewLine();
      ImGui::SetCursorPosX((SCREEN_WIDTH / 3) - 25);

      if (ImGui::Button("New Game")) {
        mainMenu = false;
      }
      ImGui::SameLine();
      if (ImGui::Button("Level Editor (WIP)")) {
        // Open web editor in default browser
        const char *editorUrl = "http://localhost:5173/?";
#ifdef _WIN32
        ShellExecuteA(NULL, "open", editorUrl, NULL, NULL, SW_SHOWNORMAL);
// TODO: Linux Web editor execution
#endif
        std::cout << "Opening web editor..." << std::endl;
      }
      ImGui::SameLine();
      if (ImGui::Button("Quit Game")) {
        exit(1);
      }
      ImGui::SameLine();
      ImGui::SetCursorPosY((SCREEN_HEIGHT)-30);
      ImGui::SetCursorPosX(0);
      if (ImGui::Button("About")) {
        ImGui::OpenPopup("License Info");
      }
      if (ImGui::BeginPopupModal("License Info", NULL,
                                 ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(
            "Copyright (C) [2025] [Jacob Lowe]\n"
            "\n"
            "This program is free software: you can redistribute it and/or "
            "modify\n"
            "it under the terms of the GNU Affero General Public License as\n"
            "published by the Free Software Foundation, either version 3 of "
            "the\n"
            "License, or (at your option) any later version.\n"
            "\n"
            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU Affero General Public License for more details.\n"
            "\n"
            "You should have received a copy of the GNU Affero General Public "
            "License\n"
            "along with this program.  If not, see "
            "<https://www.gnu.org/licenses/>");
        if (ImGui::Button("Close")) {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }
    }
    ImGui::End();
  }
}

// Recompile textures based on screen size
// Effects fill screen and the entity manager
// Effect gravity in the same way
void Application::recompileTextures() {
  terrain_gen->fillScreen(getWindow());
  entityManager->scaleEntities(window);
  phys_eng->setGravity(.98 / (scaleFactorAvg));
  std::cout << "Gravity is now " << phys_eng->getGravity() << std::endl;
}
// Check the resize and recompile the textures based on the new window
void Application::checkResize() {
  SDL_GetWindowSize(window, &current_width, &current_height);
  if ((current_width != past_width) || (current_height != past_height)) {
    recompileTextures();
    past_width = current_width;
    past_height = current_height;
    scaleFactorX = (float)current_width / SCREEN_WIDTH;
    scaleFactorY = (float)current_height / SCREEN_HEIGHT;
    std::cout << "The Scale factor is now " << scaleFactorX << "x"
              << scaleFactorY << std::endl;
    std::cout << "Window Resized to " << current_width << "x" << current_height
              << std::endl;
  }
}

// Debug menu rendering
void Application::renderDebugMenu() {
  // Frame actions
  Entity &player = *((entityManager->getEntities()
                          .data()[0])); // This should go into a header file
                                        // for the reference to the player

  if (ImGui::Button("Recompile Textures and Entity Positions")) {
    recompileTextures();
    player.entityFalling = false;
  }
  ImGui::Text("Player Position [%d,%d]",
              (entityManager->getEntities()[0])->getTileX(),
              (entityManager->getEntities()[0])->getTileY());
  if (ImGui::Button("Quit")) {
    exit(1);
  }
  if (ImGui::CollapsingHeader("Performance Settings")) {
    static int f = fps;
    if (ImGui::SliderInt("Frame Rate Cap", &f, 10, 150)) {
      fps = static_cast<uint64_t>(f);
    }
  }
  if (ImGui::CollapsingHeader("Advanced Settings and Statistics")) {
    ImGui::Text("Gameplay Debugging");
    if (ImGui::Checkbox("Show Player Hitbox", &debugPlayerHitbox)) {
      player.hitBoxToggle();
    }
    if (ImGui::Checkbox("Show Enemy Hitbox", &debugEnemyHitbox)) {
      // TODO: Enemy hitbox toggle here
      for (size_t i = 1; i < entityManager->getEntities().size(); i++) {
        Entity &entity = *((entityManager->getEntities().data()[i]));
        int e_type = entity.getEntityType();
        if (e_type == 2) {
          entity.hitBoxToggle();
        }
      }
    }
    if (ImGui::Checkbox("Show Block Hitboxes", &debugBlockHitbox)) {
      std::vector<Block> *blocks = terrain_gen->getBlockVector();
      for (Block &b : *blocks) {
        b.toggleHitboxRender();
      }
    }

    int current_width, current_height;
    SDL_GetWindowSize(window, &current_width, &current_height);
    ImGui::Text("Window Resolution [%d,%d]", current_width, current_height);
    ImGui::Text("Mouse Position [%d,%d]", xMouse, yMouse);
    ImGui::Text("Tilemap Position [%d,%d]", xMouse / 32, yMouse / 32);
    ImGui::Text("Mouse Down: %s", (mouseDown) ? "true" : "false");
  }
}

// Called in render to render all Blocks and entities
void Application::renderBlockEntities() {
  std::vector<Block> *terrain_vector = terrain_gen->getBlockVector();
  for (Block &block : *terrain_vector) // Iterate
  {
    block.draw(renderer);
  }

  // Enemies
  // SDL_RenderCopy(renderer, enemy->getTexture(), enemy->getRectTex(),
  //               enemy->getRect());
  // Entity
  for (auto &entity : entityManager->getEntities()) {
    entity->updateTexture(phys_eng, terrain_gen,
                          window); // Update entity texture
    SDL_RenderCopy(renderer, entity->getTexture(), entity->getRectTex(),
                   entity->getRect());

    // Hitbox Rendering
    if (entity->hitboxCheck()) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      SDL_RenderDrawRect(renderer, entity->getHitboxRect());
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
  }
}

// Destroy window when application is closed
void Application::clean() {
  delete terrain_gen;
  SDL_DestroyWindow(window); // destroy the window
  SDL_Quit();                // quit and delete all SDL
}
