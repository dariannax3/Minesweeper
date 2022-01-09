#include "../inc/Minesweeper.hpp"

int main(){
    Minesweeper minesweeper(std::make_shared<StdPlayerInput>(), std::make_shared<StdRandomRangeGenerator>(0,8));
    minesweeper.play();
    return 0;
}
