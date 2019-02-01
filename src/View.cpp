#include "View.h"

View::View(SDL_Renderer* _renderer, Board *_board)
{
    renderer = _renderer;
    board = _board;

    SDL_Surface* groundSurface = IMG_Load("res/img/grass.png");
    groundTex = SDL_CreateTextureFromSurface(renderer, groundSurface);
    SDL_FreeSurface(groundSurface);

    SDL_Surface* oSurface = IMG_Load("res/img/o.png");
    oTex = SDL_CreateTextureFromSurface(renderer, oSurface);
    SDL_FreeSurface(oSurface);

    SDL_Surface* xSurface = IMG_Load("res/img/x.png");
    xTex = SDL_CreateTextureFromSurface(renderer, xSurface);
    SDL_FreeSurface(xSurface);

    TTF_Init();
    font = TTF_OpenFont("res/fonts/OpenSans-Regular.ttf", 180);
}

View::~View()
{
    //dtor
}


void View::draw()
{
    int winner = board->getWinner();

    if (winner > 0 && font != nullptr) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, winner == 1 ? "Player wins" : "Computer wins", {255, 255, 255});
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect Message_rect;
        Message_rect.x = 50;
        Message_rect.y = 60;
        Message_rect.w = 700;
        Message_rect.h = 100;
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    }

    if (board->isDone()) {
        SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(font, "Click to play again.", {255, 255, 255});
        SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);

        SDL_Rect Message2_rect;
        Message2_rect.x = 50;
        Message2_rect.y = 360;
        Message2_rect.w = 700;
        Message2_rect.h = 100;
        SDL_RenderCopy(renderer, Message2, NULL, &Message2_rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect r;
    SDL_Rect rect2d;

    r.w = mapTileWidth;
    r.h = mapTileHeight;
    rect2d.w = mapTile2DWidth;
    rect2d.h = mapTile2DHeight;

    for (int row = 0; row < board->mapSize; row++) {
        for (int column = 0; column < board->mapSize; column++) {
            Point p = IsoConvert::twoDToIso(mapTile2DWidth * column, mapTile2DHeight * row);
            r.x = p.x + mapIsoOffsetX;
            r.y = p.y + mapIsoOffsetY;
            rect2d.x = (mapTile2DWidth * column) + map2DoffsetX;
            rect2d.y = (mapTile2DHeight * row) + map2DoffsetY;

            if (board->points[row][column] > 0) {
                SDL_RenderCopy(renderer, board->points[row][column] == 1 ? xTex : oTex, NULL, &r);

                if (board->points[row][column] == 1) {
                    SDL_SetRenderDrawColor(renderer, 38, 97, 149, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 211, 66, 66, 255);
                }


                SDL_RenderFillRect(renderer, &rect2d);
            } else {
                SDL_RenderCopy(renderer, groundTex, NULL, &r);

                SDL_SetRenderDrawColor(renderer, 139, 181, 74, 255);
                SDL_RenderFillRect(renderer, &rect2d);
            }

            SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);
            SDL_RenderDrawRect(renderer, &rect2d);
        }
    }
}

void View::click(int screenX, int screenY)
{
    int screenXwithOffset = screenX - mapIsoOffsetX;
    int screenYwithOffset = screenY - mapIsoOffsetY;

    clickedPoint2D = IsoConvert::isoToTwoD(screenXwithOffset, screenYwithOffset);
    clickedPoint2D.x = clickedPoint2D.x - (mapTile2DWidth / 2);
    clickedPoint2D.y = clickedPoint2D.y + (mapTile2DHeight / 2);

    int column = ceil(clickedPoint2D.x / mapTile2DWidth) -1;
    int row = ceil(clickedPoint2D.y / mapTile2DHeight) - 1;

    if (row >= 0 && row < board->mapSize && column >= 0 && column < board->mapSize && board->points[row][column] == 0) {
        board->setPointValue(row, column, 1);
        board->computerMove();
    }
}


