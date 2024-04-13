#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <memory>
#include "game.h"
#include "../Logger/logger.h"

Game::Game() {
    isRunning = false;
    registry = std::make_unique<Registry>();
    Logger::info("Game obj constructed");
    Logger::err("example error");
}

Game::~Game() {
    Logger::info("Game obj destroyed");
}

void Game::initialize() {
    // init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::err("Error init SDL2");
        return;
    }

    // create the application window
    window = SDL_CreateWindow(
        "proto game engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    if (!window) {
        Logger::err("Error initializing SDL2 window");
    }

    // initialize renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        Logger::err("Error initializing SDL2 Renderer");
    }
    isRunning = true;

}

void Game::run() {
    setup();
    while(isRunning) {
        procInput();
        update();
        render();
    }
}

// glm::vec2 playerPos;
// glm::vec2 playerVel;
void Game::setup() {
    Entity tank = registry->createEntity();
    Entity truck = registry->createEntity();
    // playerPos = glm::vec2(10.0, 15.0);
    // playerVel = glm::vec2(270, 310);
}

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
    deltaTime = static_cast<double>(SDL_GetTicks()- prevFrameMillisecs) / 1000.0;
    
    prevFrameMillisecs = SDL_GetTicks();
    
    updatePlayer();
    
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
    SDL_RenderClear(renderer);
    // TODO: render game here

    // SDL_Rect dstrect = {
    //     static_cast<int>(playerPos.x),
    //     static_cast<int>(playerPos.y),
    //     32,
    //     32
    // };

    // // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // // SDL_RenderFillRect(renderer, &rect);
    
    // SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);

    // SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    // SDL_DestroyTexture(texture);
    /*
    swaps back and front buffers, the back buffer is what
    we were drawing to prior to presenting
    */
    SDL_RenderPresent(renderer);
}

void Game::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
