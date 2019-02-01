#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <View.h>
#include <Board.h>
#include <cstdlib>
#include <iostream>
#include <string>

class Game
{
    public:
        Game();
        virtual ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running();
        void restartGame();
    protected:

    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        View *view;
        Board *board;
};

#endif // GAME_H
