#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const int MAX_FPS = 240;
const int MS_PER_FRAME = 1000/MAX_FPS;

class Game {
    private:
        Uint32 prevFrameMillisecs = 0;
        double deltaTime = 0.0;
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        void initialize();
        void run();
        void setup();
        void procInput();
        void update();
        void render();
        void destroy();
        void updatePlayer();
};
#endif