#ifndef GAME_H
#define GAME_H

#include "../AssetMgr/asset_mgr.h"
#include "../ECS/ecs.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

const int MAX_FPS = 240;
const int MS_PER_FRAME = 1000 / MAX_FPS;

class Game {
private:
  Uint32 prevFrameMillisecs = 0;
  double deltaTime = 0.0;
  bool isRunning;
  bool debugActive;
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::unique_ptr<Registry> registry;
  std::unique_ptr<AssetMgr> assetMgr;

public:
  Game();
  ~Game();
  void initialize();
  void run();
  void parseMap(std::string mapTextureStr, std::string mapFileStr, int tileW,
                int tileH, int maxTilesInTextureX, int mapWidth,
                glm::vec2 scale);
  void loadLevel(int level);
  void setup();
  void procInput();
  void update();
  void render();
  void destroy();
  void updatePlayer();
};

#endif