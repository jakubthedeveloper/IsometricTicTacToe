#include "Board.h"

Board::Board()
{
    //ctor
}

Board::~Board()
{
    //dtor
}

void Board::setPointValue(int row, int column, int value)
{
    bool valid = true;
    if (row < 0 || row > 2 || column < 0 || column > 2) {
        std::cout << "Invalid point coordinates" << std::endl;
        valid = false;
    }

    if (value < 0 || value > 2) {
        std::cout << "Invalid point value" << std::endl;
        valid = false;
    }

    if (!valid) {
        return;
    }

    points[row][column] = value;
    freeFields--;

    checkIfDone();
}


void Board::checkIfDone()
{
    if (freeFields <= 5) // can't win in first 4 moves
    {
        for (int c = 0; c < winningCombinationsNumber; c++) { // combination
            if (
                points[winningCombinations[c][0][0]][winningCombinations[c][0][1]] > 0
                &&
                (
                    points[winningCombinations[c][0][0]][winningCombinations[c][0][1]]
                    ==
                    points[winningCombinations[c][1][0]][winningCombinations[c][1][1]]
                )
                &&
                (
                    points[winningCombinations[c][1][0]][winningCombinations[c][1][1]]
                    ==
                    points[winningCombinations[c][2][0]][winningCombinations[c][2][1]]
                )
            ) {
                done = true;
                winner = points[winningCombinations[c][0][0]][winningCombinations[c][0][1]];
                return;
            }
        }
    }

    if (freeFields <= 0) {
        done = true;
        return;
    }
}

bool Board::isDone()
{
    return done;
}

void Board::restart()
{
    computerStarts = !computerStarts;
    for (int row = 0; row < mapSize; row++) {
        for (int column = 0; column < mapSize; column++) {
            points[row][column] = 0;
        }
    }

    freeFields = 9;
    done = false;
    winner = 0;

    if (computerStarts) {
        computerMove();
    }
}


void Board::computerMove()
{
    if (done) {
        return;
    }

    int row = -1;
    int column = -1;
    int value = -1;

    do {
        row = rand() % 3;
        column = rand() % 3;
        value = points[row][column];
    } while (value > 0);

    if (row >= 0 && column >= 0) {
        setPointValue(row, column, 2);
    }
}

int Board::getWinner()
{
    return winner;
}
