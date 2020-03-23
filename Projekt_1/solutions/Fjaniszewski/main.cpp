//
// Created by filip on 20.03.2020.
//

#include "MinesweeperBoard.h"

int main(){
    srand(time(nullptr));
    MinesweeperBoard Board1(9,7,DEBUG);
    Board1.debug_display();
    Board1.revealField(6,0);
    std::cout<<"info: "<<Board1.getFieldInfo(6,0)<<"\n";
    std::cout<<Board1.isRevealed(6,0)<<"\n";
    std::cout<<Board1.countMines(6,0)<<"\n";
    Board1.debug_display();
}

