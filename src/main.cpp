#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <iostream>
#include <sol/sol.hpp>

#include "Game/game.h"

int main(int argc, char *argv[]) {
  // while(true) {
  //     // game loop: process input, update, render
  // }
  Game game;

  game.initialize();
  game.run();
  game.destroy();

  return 0;
}
