#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <IsoConvert.h>
#include <Board.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>

class View
{
    public:
        View(SDL_Renderer* renderer, Board *board);
        virtual ~View();
        void draw();
        int getMapWidth();
        int getMapHeight();
        void click(int screenX, int screenY);
    protected:

    private:
        SDL_Renderer *renderer;
        SDL_Texture* groundTex;
        SDL_Texture* oTex;
        SDL_Texture* xTex;
        Board *board;
        int mapTileWidth = 100;
        int mapTileHeight = 65;
        int mapTile2DWidth = 50;
        int mapTile2DHeight = 50;
        /*int points[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };*/
        Point clickedPoint2D;
        int mapIsoOffsetX = 200;
        int mapIsoOffsetY = 190;
        int map2DoffsetX = 480;
        int map2DoffsetY = 190;
        TTF_Font* font = nullptr;
};

#endif // MAP_H
