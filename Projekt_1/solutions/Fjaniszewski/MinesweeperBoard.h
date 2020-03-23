//
// Created by filip on 20.03.2020.
//

#ifndef PROJECT_1_MINESWEEPERBOARD_H
#define PROJECT_1_MINESWEEPERBOARD_H


#include "Field.h"
#include <iostream>

enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

class MinesweeperBoard
{
public:
    MinesweeperBoard(int width, int height, GameMode mode);
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;
private:
    void buildField();
    Field board[100][100];
    int width;
    int height;
    GameMode mode;
    GameState state;
};

#endif //PROJECT_1_MINESWEEPERBOARD_H