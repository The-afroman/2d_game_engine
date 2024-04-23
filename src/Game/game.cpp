#include "game.h"
#include "../Components/animation_component.h"
#include "../Components/box_collider_component.h"
#include "../Components/rigid_body_component.h"
#include "../Components/transform_component.h"
#include "../Logger/logger.h"
#include "../Systems/animation_system.h"
#include "../Systems/collision_system.h"
#include "../Systems/debug_collision_system.h"
#include "../Systems/movement_system.h"
#include "../Systems/render_system.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <sstream>

Game::Game() {
  isRunning = false;
  debugActive = false;
  registry = std::make_unique<Registry>();
  assetMgr = std::make_unique<AssetMgr>();
  Logger::info("Game obj constructed");
}

Game::~Game() { Logger::info("Game obj destroyed"); }

void Game::initialize() {
  // init sdl
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::err("Error init SDL2");
    return;
  }

  // create the application window
  Uint32 windowFlags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE |
                       SDL_WINDOW_ALWAYS_ON_TOP;
  window = SDL_CreateWindow("proto game engine", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600, windowFlags);
  if (!window) {
    Logger::err("Error initializing SDL2 window");
  }

  // initialize renderer
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    Logger::err("Error initializing SDL2 Renderer");
  }
  isRunning = true;
}

void Game::run() {
  setup();
  while (isRunning) {
    procInput();
    update();
    render();
  }
}

void Game::parseMap(std::string mapTextureStr, std::string mapFileStr,
                    int tileW, int tileH, int maxTilesInTextureX, int mapWidth,
                    glm::vec2 scale) {
  std::ifstream mapFile;
  mapFile.open(mapFileStr);
  if (!mapFile.is_open()) {
    Logger::err("Failed to open " + mapFileStr);
    return;
  }

  std::string line;
  int tileidx = 0;
  while (std::getline(mapFile, line)) {
    std::stringstream ss(line);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
      int tileNum = atoi(tok.c_str());
      int column = tileNum % maxTilesInTextureX;
      int row = tileNum / maxTilesInTextureX;
      Entity tile = registry->createEntity();
      float posx = static_cast<float>(((tileidx * tileW) % mapWidth));
      float posy = static_cast<float>(((tileidx * tileW) / mapWidth) * tileW);
      glm::vec2 pos = {posx, posy};
      pos *= scale;
      Logger::info(std::to_string(posx) + " " + std::to_string(posy));
      tile.addComponent<SpriteComponent>(mapTextureStr, tileW, tileH, 0,
                                         column * tileW, row * tileH);
      tile.addComponent<TransformComponent>(pos, scale, 0.0);
      tileidx++;
    }
  }
}

void Game::loadLevel(int level) {
  // add the systems required by the game
  registry->addSystem<MovementSystem>();
  registry->addSystem<RenderSystem>();
  registry->addSystem<AnimationSystem>();
  registry->addSystem<CollisionSystem>();
  registry->addSystem<DebugCollisionSystem>();

  // add assets to AssetMgr
  assetMgr->addTexture(renderer, "tank-image",
                       "./assets/images/tank-tiger-right.png");
  assetMgr->addTexture(renderer, "chopper-animation",
                       "./assets/images/chopper.png");
  // load the tilemap
  assetMgr->addTexture(renderer, "jungle-tilemap",
                       "./assets/tilemaps/jungle.png");
  glm::vec2 mapScale = {2.0, 2.0};
  int tileSize = 32;
  int maxTilesInTextureX = 10;
  int mapWidth = 800;

  parseMap("jungle-tilemap", "./assets/tilemaps/jungle.map", tileSize, tileSize,
           maxTilesInTextureX, mapWidth, mapScale);
  // create entity
  Entity tank = registry->createEntity();
  tank.addComponent<TransformComponent>(glm::vec2(10.0, 10.0),
                                        glm::vec2(1.0, 1.0), 0.0);
  tank.addComponent<RigidBodyComponent>(glm::vec2(10.0, 10.0));
  tank.addComponent<SpriteComponent>("tank-image", 32, 32, 1);
  tank.addComponent<BoxColliderComponent>(32, 32);

  Entity chopper = registry->createEntity();
  chopper.addComponent<TransformComponent>(glm::vec2(150.0, 150.0),
                                           glm::vec2(1.0, 1.0), 0.0);
  chopper.addComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
  chopper.addComponent<SpriteComponent>("chopper-animation", 32, 32, 1);
  chopper.addComponent<AnimationComponent>(2, 10, true);
  chopper.addComponent<BoxColliderComponent>(32, 32);
}

// glm::vec2 playerPos;
// glm::vec2 playerVel;
void Game::setup() { loadLevel(1); }

void Game::procInput() {
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      } else if (sdlEvent.key.keysym.sym == SDLK_F3) {
        debugActive = !debugActive;
      }
      break;
    }
  }
}

void Game::updatePlayer() {
  // int windowX;
  // int windowY;
  // SDL_GetWindowSize(window, &windowX, &windowY);
  // if (playerPos.x+32 > windowX) {
  //     playerVel.x *= -1;
  //     playerPos.x = windowX-32;
  // } else if (playerPos.x < 0) {
  //     playerVel.x *= -1;
  //     playerPos.x = 0;
  // }
  // if (playerPos.y+32 > windowY) {
  //     playerPos.y = windowY-32;
  //     playerVel.y *= -1;
  // } else if (playerPos.y < 0) {
  //     playerPos.y = 0;
  //     playerVel.y *= -1;
  // }
  // playerPos.x += playerVel.x * deltaTime;
  // playerPos.y += playerVel.y * deltaTime;
}

void Game::update() {
  // cap game loop update to MAX_FPS
  Uint32 ticksDelay = MS_PER_FRAME - (SDL_GetTicks() - prevFrameMillisecs);
  if (ticksDelay > 0 && ticksDelay <= MS_PER_FRAME) {
    SDL_Delay(ticksDelay);
  }
  deltaTime = static_cast<double>(SDL_GetTicks() - prevFrameMillisecs) / 1000.0;

  prevFrameMillisecs = SDL_GetTicks();

  // update the registry
  registry->update();
  // ask systems to update
  registry->getSystem<MovementSystem>().update(deltaTime);
  registry->getSystem<AnimationSystem>().update();
  registry->getSystem<CollisionSystem>().update();

  updatePlayer();
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
  SDL_RenderClear(renderer);
  // sort entites
  registry->getSystem<RenderSystem>().sortByZIdx();
  // render
  registry->getSystem<RenderSystem>().update(renderer, assetMgr);
  registry->getSystem<DebugCollisionSystem>().update(renderer, debugActive);
  /*
  swaps back and front buffers, the back buffer is what
  we were drawing to prior to presenting
  */
  SDL_RenderPresent(renderer);
}

void Game::destroy() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
