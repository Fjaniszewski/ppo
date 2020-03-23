//
// Created by filip on 20.03.2020.
//

#include "MinesweeperBoard.h"

int main(){
    srand(time(nullptr));
    MinesweeperBoard Board1(9,7,DEBUG);
    Board1.debug_display();
    Board1.revealField(7,6);
    Board1.toggleFlag(0,7);
    std::cout<<"info: "<<Board1.getFieldInfo(0,7)<<"\n";
    std::cout<<"info: "<<Board1.getFieldInfo(7,6)<<"\n";
    std::cout<<Board1.isRevealed(7,6)<<"\n";
    std::cout<<Board1.countMines(7,6)<<"\n";
    std::cout<<Board1.hasFlag(0,7);
}
