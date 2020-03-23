//
// Created by filip on 20.03.2020.
//

#include "MinesweeperBoard.h"
#include <iostream>
#include <cstdlib>

MinesweeperBoard::MinesweeperBoard(int  width, int height, GameMode mode) {
    this->width = width;
    this->height = height;
    this->mode = mode;
    this->buildField();
};

void MinesweeperBoard::debug_display() const{
    for(int i=0;i<this->getBoardHeight();i++) {
        for (int j=0; j <this->getBoardWidth(); j++)
        {
            std::cout<<"[";
            if(board[j][i].hasMine) std::cout<<"M";
            else std::cout<<".";
            if(board[j][i].isRevealed) std::cout<<"o";
            else std::cout<<".";
            if(board[j][i].hasFlag) std::cout<<"f";
            else std::cout<<".";
            std::cout<<"]";
        }
        std::cout<<"\n";
    }
}

int MinesweeperBoard::getBoardWidth() const{
    return this->width;
}
int MinesweeperBoard::getBoardHeight() const{
    return this->height;
}
int MinesweeperBoard::getMineCount() const{
    if(mode==EASY){
        return height*width*0.1;
    }
    if(mode==NORMAL){
        return height*width*0.2;
    }
    if(mode==HARD){
        return height*width*0.3;
    }
    if(mode==DEBUG){
        if (height%2==0) return height/2+width+height-2;
        if (height%2!=0) return height/2+1+width+height-2;
    }
}


void MinesweeperBoard::buildField() {
    if (mode == DEBUG) {
        for (int i = 0; i < this->getBoardWidth(); i++) board[i][0] = {true, false, false};
        for (int i = 0; i < this->getBoardHeight(); i++) if (i % 2 == 0) board[0][i] = {true, false, false};
        for (int i = 0; i < this->getBoardHeight(); i++) board[i][i] = {true, false, false};
    } else {
        for (int i = 0; i < this->getMineCount(); i++) {
            int random1 = rand() % this->getBoardHeight() ;
            int random2 = rand() % this->getBoardWidth() ;
            if(!board[(random2 )][(random1 )].hasMine) board[(random2 )][(random1 )] = {true, false, false};
            else {
                i--;
            }
        }
    }
}

int MinesweeperBoard::countMines(int y, int x) const {
    if (x > 0 && x < this->getBoardWidth() && y > 0 && y < this->getBoardHeight()) {
        if (!board[x][y].isRevealed) return -1;
        int minecounter = 0;
        if (board[x][y - 1].hasMine) minecounter++;
        if (board[x][y + 1].hasMine) minecounter++;
        if (board[x + 1][y].hasMine) minecounter++;
        if (board[x - 1][y].hasMine) minecounter++;
        if (board[x - 1][y - 1].hasMine) minecounter++;
        if (board[x - 1][y + 1].hasMine) minecounter++;
        if (board[x + 1][y - 1].hasMine) minecounter++;
        if (board[x + 1][y + 1].hasMine) minecounter++;
        return minecounter;
    }
    if (x == 0 && y>0) {
        if (!board[x][y].isRevealed) return -1;
        int minecounter = 0;
        if (board[x][y - 1].hasMine) minecounter++;
        if (board[x][y + 1].hasMine) minecounter++;
        if (board[x + 1][y].hasMine) minecounter++;
        if (board[x + 1][y - 1].hasMine) minecounter++;
        if (board[x + 1][y + 1].hasMine) minecounter++;
        return minecounter;
    }
    if (y==0 && x>0){
    if (!board[x][y].isRevealed) return -1;
    int minecounter = 0;
    if (board[x][y + 1].hasMine) minecounter++;
    if (board[x + 1][y].hasMine) minecounter++;
    if (board[x - 1][y].hasMine) minecounter++;
    if (board[x - 1][y + 1].hasMine) minecounter++;
    if (board[x + 1][y + 1].hasMine) minecounter++;
    return minecounter;
    }
    if (x==0 && y==0){
        if (!board[x][y].isRevealed) return -1;
        int minecounter = 0;
        if (board[x][y + 1].hasMine) minecounter++;
        if (board[x + 1][y].hasMine) minecounter++;
        if (board[x + 1][y + 1].hasMine) minecounter++;
        return minecounter;
    }
    return -1;
}

bool MinesweeperBoard::hasFlag(int y, int x) const{
    if(x>-1 && x<this->getBoardWidth() && y>-1 && y<this->getBoardHeight()) {
    return board[x][y].hasFlag;
    }
    return false;
}

void MinesweeperBoard::toggleFlag(int y, int x){
    if(x>-1 && x<this->getBoardWidth() && y>-1&& y<this->getBoardHeight()) {
        if(state == RUNNING) {
            if (!board[x][y].isRevealed) board[x][y].hasFlag = true;
        }
    }
}

void MinesweeperBoard::revealField(int y, int x){
    if(x>-1 && x<this->getBoardWidth() && y>-1 && y<this->getBoardHeight()) {
        if (!board[x][y].isRevealed) {
            if (state == RUNNING) {
                if (!board[x][y].hasFlag) {
                    if (board[x][y].hasMine) {
                        board[x][y].isRevealed=true;
                        state = FINISHED_LOSS;
                    }
                    else board[x][y].isRevealed=true;
                }
            }
        }
    }
}

bool MinesweeperBoard::isRevealed(int y, int x) const{
    return board[x][y].isRevealed;
}

GameState MinesweeperBoard::getGameState() const{
    int flagggedMinesCount=0;
    int unrevealedFieldsCount=0;
    for(int i=0;i<this->getBoardHeight();i++) {
        for (int j = 0; j < this->getBoardWidth(); j++){
            if(board[i][j].isRevealed && board[i][j].hasMine) return FINISHED_LOSS;
            if(board[i][j].hasFlag && board[i][j].hasMine) flagggedMinesCount++;
            if(!board[i][j].isRevealed) unrevealedFieldsCount++;
        }
    }
    if(flagggedMinesCount==this->getMineCount()) return FINISHED_WIN;
    if (unrevealedFieldsCount==this->getMineCount()) return FINISHED_WIN;
    return RUNNING;
}

char MinesweeperBoard::getFieldInfo(int y, int x) const{
    if((x>this->getBoardWidth() || y>this->getBoardHeight()) || (x<0 || y< 0)) return '#';
    if(!board[x][y].isRevealed && board[x][y].hasFlag) return 'F';
    if(!board[x][y].isRevealed && !board[x][y].hasFlag) return '_';
    if(board[x][y].isRevealed && board[x][y].hasMine) return 'x';
    if(board[x][y].isRevealed && this->countMines(x,y)==0) return ' ';
    int mines = this-> countMines(y,x);
    return mines != 0 ? (char) mines+48 : ' ';
}