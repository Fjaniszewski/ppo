//
// Created by filip on 21.03.2020.
//

#include "MinesweeperBoard.h"
int main(){
    MinesweeperBoard Board1(9,7,EASY);
    Board1.debug_display();
    Board1.revealField(7,6);
    Board1.toggleFlag(0,7);
    std::cout<<"info: "<<Board1.getFieldInfo(0,7)<<"\n";
    std::cout<<"info: "<<Board1.getFieldInfo(7,6)<<"\n";
}
