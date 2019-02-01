#ifndef BOARD_H
#define BOARD_H
#include <cstdlib>
#include <iostream>
#include <string>

class Board
{
    public:
        Board();
        virtual ~Board();
        int mapSize = 3;
        int points[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };
        bool isDone();
        void restart();
        void computerMove();
        void setPointValue(int x, int y, int value);
        int getWinner();
    protected:

    private:
        void checkIfDone();
        int freeFields = 9;
        bool computerStarts = false;
        int winningCombinationsNumber = 8;
        int winningCombinations[8][3][2] = {
            {{0,0},{0,1},{0,2}},
            {{1,0},{1,1},{1,2}},
            {{2,0},{2,1},{2,2}},

            {{0,0},{1,1},{2,2}},
            {{0,2},{1,1},{2,0}},

            {{0,0},{1,0},{2,0}},
            {{0,1},{1,1},{2,1}},
            {{0,2},{1,2},{2,2}}
        };
        int winner = 0;
        bool done = false;
};

#endif // BOARD_H
