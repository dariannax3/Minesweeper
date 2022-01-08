#include "../inc/Gameboard.hpp"
#include <iostream>
#include <chrono>
#include <unistd.h>

void Gameboard::uncoverAllFields() {
    for (auto& row : board_) {
        for (auto& field : row) {
            field.visibility = Visibility::uncovered;
        }
    }
}
bool Gameboard::isFieldInGameboard(const int x, const int y) {
    return x >= 0 && y >= 0 && x <= getWidth() && y <= getHeight();
}

bool Gameboard::isFieldMined(const int x, const int y) {
    return isFieldInGameboard(x, y) && getFieldAt(x, y).bombility == Bombility::mined;
}

bool Gameboard::isFieldAdjacentToBomb(const int x, const int y) {
    return (   isFieldMined(x + 1, y) 
            || isFieldMined(x - 1, y) 
            || isFieldMined(x, y + 1) 
            || isFieldMined(x, y - 1) 
            || isFieldMined(x + 1, y - 1) 
            || isFieldMined(x + 1, y + 1) 
            || isFieldMined(x - 1, y - 1) 
            || isFieldMined(x - 1, y + 1));
}


void Gameboard::uncoverOneFieldIfPossible(const int x, const int y) {
    if(getFieldAt(x, y).visibility == Visibility::covered &&
       isFieldInGameboard(x, y))
        uncoverOneField(x, y);
}

void Gameboard::uncoverOneField(const int x, const int y) {
    printBoardVisibility();
    
    if(isFieldAdjacentToBomb(x, y)) {
        getFieldAt(x, y).visibility = Visibility::uncovered;
        return;
    }
    
    getFieldAt(x, y).visibility = Visibility::uncovered;

    uncoverOneFieldIfPossible(x - 1, y - 1);
    uncoverOneFieldIfPossible(x - 1, y);
    uncoverOneFieldIfPossible(x - 1, y + 1);
    uncoverOneFieldIfPossible(x, y + 1);
    uncoverOneFieldIfPossible(x + 1, y + 1);
    uncoverOneFieldIfPossible(x + 1, y);
    uncoverOneFieldIfPossible(x + 1, y - 1);
    uncoverOneFieldIfPossible(x, y - 1);
}

int Gameboard::countAdjacentBombAt(const int x, const int y){
    int counter = 0;

    if(isFieldMined(x + 1, y)){
        counter ++;
    }
    if(isFieldMined(x - 1, y)){
        counter ++;
    }
    if(isFieldMined(x, y + 1)){
        counter ++;
    }
    if(isFieldMined(x, y - 1)){
        counter ++;
    }
    if(isFieldMined(x + 1, y - 1)){
        counter ++;
    }
    if(isFieldMined(x + 1, y + 1) ){
        counter ++;
    }
     if(isFieldMined(x - 1, y - 1)){
        counter ++;
    }
    if(isFieldMined(x - 1, y + 1) ){
        counter ++;
    } 
    return counter;
}

void Gameboard::printBoardVisibility(){
    for(int i = 0; i < getWidth(); i++){
        for(int j = 0; j < getHeight(); j++)
        {
            if( getFieldAt(i, j).visibility == Visibility::covered){
                std::cout << " X";
            }
            else {
                if( isFieldAdjacentToBomb(i, j) )
                    std::cout << " " <<  countAdjacentBombAt(i, j);
                else 
                    std::cout << " O";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    usleep(1000000);
}

int Gameboard::getWidth() const {
    return board_[0].size();
}

int Gameboard::getHeight() const {
    return board_.size();
}

Field& Gameboard::getFieldAt(int row, int column) {
    return board_[row][column];
}

void Gameboard::setBomb(const int x, const int y) {
    Field& field = getFieldAt(x, y);
    field.bombility = Bombility::mined;
}