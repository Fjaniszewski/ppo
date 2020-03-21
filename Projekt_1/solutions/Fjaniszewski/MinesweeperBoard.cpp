//
// Created by filip on 20.03.2020.
//

#include "MinesweeperBoard.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

MinesweeperBoard::MinesweeperBoard(int  width, int height, GameMode mode) {
    srand(time(nullptr));                      //srand should be run only once in a program
    this->width = width;
    this->height = height;
    this->mode = mode;
    MinesweeperBoard::buildField();
};

void MinesweeperBoard::debug_display() const{
    for(int i=0;i<this->MinesweeperBoard::getBoardHeight();i++) {
        for (int j=0; j <this->MinesweeperBoard::getBoardWidth(); j++)
        {
            std::cout<<"[";
            if(board[j][i].hasMine == 1) std::cout<<"M";
            else std::cout<<".";
            if(board[j][i].isRevealed == 1) std::cout<<"o";
            else std::cout<<".";
            if(board[j][i].hasFlag == 1) std::cout<<"f";
            else std::cout<<".";
            std::cout<<"]";
        }
        std::cout<<"\n";
    }
}

int MinesweeperBoard::getBoardWidth() const{
    return width;
}
int MinesweeperBoard::getBoardHeight() const{
    return height;
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
        for (int i = 0; i < this->MinesweeperBoard::getBoardWidth(); i++) board[i][0] = {true, false, false};
        for (int i = 0; i < this->MinesweeperBoard::getBoardHeight(); i++) if (i % 2 == 0) board[0][i] = {true, false, false};
        for (int i = 0; i < this->MinesweeperBoard::getBoardHeight(); i++) board[i][i] = {true, false, false};
    } else {
        for (int i = 0; i < this->MinesweeperBoard::getMineCount(); i++) {
            start:
            int random1 = rand() % MinesweeperBoard::getBoardHeight() + 1;
            int random2 = rand() % MinesweeperBoard::getBoardWidth() + 1;
            if(board[(random2 - 1)][(random1 - 1)].hasMine!=1) board[(random2 - 1)][(random1 - 1)] = {true, false, false};
            else goto start;
        }
    }
}

int MinesweeperBoard::countMines(int x, int y) const{
    if(board[x][y].isRevealed==0) return -1;
    if(x>MinesweeperBoard::getBoardWidth() || y>MinesweeperBoard::getBoardHeight()) return -1;
    else{
        int minecounter=0;
        if(board[x][y-1].hasMine==1) minecounter++;
        if(board[x][y+1].hasMine==1) minecounter++;
        if(board[x+1][y].hasMine==1) minecounter++;
        if(board[x-1][y].hasMine==1) minecounter++;
        if(board[x-1][y-1].hasMine==1) minecounter++;
        if(board[x-1][y+1].hasMine==1) minecounter++;
        if(board[x+1][y-1].hasMine==1) minecounter++;
        if(board[x+1][y+1].hasMine==1) minecounter++;
        return minecounter;
    }
}

bool MinesweeperBoard::hasFlag(int x, int y) const{
    if(board[x][y].hasFlag==1) return true;
    if(x>MinesweeperBoard::getBoardWidth() || y>MinesweeperBoard::getBoardHeight()) return false;
    if(board[x][y].hasFlag==0) return false;
    if(board[x][y].isRevealed==1) return false;
}

void MinesweeperBoard::toggleFlag(int x, int y){
    if(board[x][y].isRevealed==0) board[x][y].hasFlag=true;
    if(x>MinesweeperBoard::getBoardWidth() || y>MinesweeperBoard::getBoardHeight());
    if(board[x][y].isRevealed==1);
    if(state==FINISHED_LOSS || state==FINISHED_WIN);
}

void MinesweeperBoard::revealField(int x, int y){
    if(x>MinesweeperBoard::getBoardWidth() || y>MinesweeperBoard::getBoardHeight());
    if(board[x][y].isRevealed==1);
    if(state==FINISHED_WIN || state==FINISHED_LOSS);
    if(board[x][y].hasFlag==1);
    if(board[x][y].hasFlag==0 && board[x][y].isRevealed==0) board[x][y].isRevealed=true;
    if(board[x][y].hasFlag==0 && board[x][y].isRevealed==0 && board[x][y].hasMine==1){
        board[x][y].isRevealed=true;
        state=FINISHED_LOSS;
    }
}

bool MinesweeperBoard::isRevealed(int x, int y) const{
    if(board[x][y].isRevealed==1) return true;
}

GameState MinesweeperBoard::getGameState() const{
    bool lost;
    int flagggedMinesCount=0;
    int unrevealedFieldsCount=0;
    for(int i=0;i<this->MinesweeperBoard::getBoardHeight();i++) {
        for (int j = 0; j < this->MinesweeperBoard::getBoardWidth(); j++){
            if(board[i][j].isRevealed==1 && board[i][j].hasMine==1) {
                lost = true;
                return FINISHED_LOSS;
            }
            if(board[i][j].hasFlag==1 && board[i][j].hasMine!=0) flagggedMinesCount++;
            if(board[i][j].isRevealed==0) unrevealedFieldsCount++;
        }
    }
    if(flagggedMinesCount==MinesweeperBoard::getMineCount()) return FINISHED_WIN;
    if(unrevealedFieldsCount==MinesweeperBoard::getMineCount()) return FINISHED_WIN;
    if(flagggedMinesCount!=MinesweeperBoard::getMineCount() && unrevealedFieldsCount!=MinesweeperBoard::getMineCount() && lost!=true) return RUNNING;
}

char MinesweeperBoard::getFieldInfo(int x, int y) const{
    if(x>MinesweeperBoard::getBoardWidth() || y>MinesweeperBoard::getBoardHeight()) return '#';
    if(board[x][y].isRevealed==0 && board[x][y].hasFlag==1) return 'F';
    if(board[x][y].isRevealed==0 && board[x][y].hasFlag==0) return '_';
    if(board[x][y].isRevealed==1 && board[x][y].hasMine==1) return 'x';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==0) return ' ';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==1) return '1';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==2) return '2';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==3) return '3';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==4) return '4';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==5) return '5';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==6) return '6';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==7) return '7';
    if(board[x][y].isRevealed==1 && MinesweeperBoard::countMines(x,y)==8) return '8';
}