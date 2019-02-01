#include "../include/Game.h"

Game::Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    srand(time(NULL));
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        board = new Board();
        view = new View(renderer, board);
        isRunning = true;
        board->restart();
    } else {
        isRunning = false;
        std::cout << "Can't init sdl" << std::endl;
    }
}

bool Game::running()
{
    return isRunning;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            std::cout << "Bye, bye" << std::endl;
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    SDL_Quit();
                    break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (board->isDone()) {
                restartGame();
            } else {
                view->click(x, y);
            }
            break;

        default:
            break;
    }
}

void Game::restartGame()
{
    board->restart();
}

void Game::update()
{

}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderClear(renderer);

    view->draw();
    //player->draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

Game::~Game()
{
    //dtor
}
