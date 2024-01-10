#include "Application.h"
#include <SDL2/SDL_scancode.h>

// Upgrade to C++ 11

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
}

Application::~Application() { std::cout << "-----Application Destroyed\n"; }

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
      entityManager->createAndAddEntity(renderer, Entity::ENEMY_E, 20, 16);
      entityManager->createAndAddEntity(renderer, Entity::ENEMY_E, 21, 16);
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
      terrain_gen->fillScreen();
      std::cout << "-----Terrain Generation Complete" << std::endl;

      // Start Physics engine
      phys_eng = new Physics();

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

// void Application::setRefreshRate() {
//   // DEVMODE dm;
//   // dm.dmSize = sizeof(dm);
//   // EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
//   // this->fps = dm.dmDisplayFrequency;
//   // std::cout << "Refresh Rate: " << this->fps << std::endl;
// }

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
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_w: {
      (*entity)->yPathEdit(Entity::Up);
      (*entity)->editMS(3);
      break;
    }
    case SDLK_a: {
      (*entity)->xPathEdit(Entity::Left);
      (*entity)->editMS(2);
      break;
    }
    case SDLK_s: {
      (*entity)->yPathEdit(Entity::Down);
      break;
    }
    case SDLK_d: {
      (*entity)->xPathEdit(Entity::Right);
      (*entity)->editMS(2);
      break;
    }
    }
    break;
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
        terrain_gen->loadLevel("DefaultLoad");
      break;
    }
    case SDLK_2: {
      if (debugMode)
        terrain_gen->loadLevel("Room");
      break;
    }
    case SDLK_3: {
      if (debugMode)
        terrain_gen->loadLevel("EmptyFloor");
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
  for (auto &entity : entityManager->getEntities()) {
    entity->checkCollision(
        phys_eng->checkRectCollision(entity->getHitboxRect(), terrain_gen),
        phys_eng); // Check entity collision with terrain
  }

  // terrain_gen->fillScreen(); // Update textures and rectangles
}

void Application::render() {
  // This should change for updating all entities
  // for (auto &entity : entityManager->getEntities()) {
  // }

  // enemy->updateTexture(phys_eng, terrain_gen);  // Update enemy texture
  SDL_RenderClear(renderer); // Clear Screen

  if (debugMode) {

    // Start the Dear ImGui frame
    SDL_SetRenderDrawColor(
        renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
        (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 1));
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    // Frame actions
    static float f = 0.0f;
    ImGui::Text("Welcome to the debug window! You can close this with ` %d",
                123);
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    // Rendering Frame
    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x,
                       io.DisplayFramebufferScale.y);
    // SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  } else {
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
      entity->updateTexture(phys_eng, terrain_gen); // Update entity texture
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
  SDL_RenderPresent(renderer);
}

void Application::clean() {
  delete terrain_gen;
  SDL_DestroyWindow(window); // destroy the window
  SDL_Quit();                // quit and delete all SDL
}
