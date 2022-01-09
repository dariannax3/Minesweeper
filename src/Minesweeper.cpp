#include "../inc/Minesweeper.hpp"
#include <iostream>

Minesweeper::Minesweeper(PlayerInputPtr playerInput,
                         RandomRangeGeneratorPtr generator)
    : player_(playerInput), generator_(generator) {}

void deleteBombDuplication(Bombs& generatedBombs) {
  std::sort(generatedBombs.begin(), generatedBombs.end());
  auto last = std::unique(generatedBombs.begin(), generatedBombs.end());
  generatedBombs.erase(last, generatedBombs.end());
}

Bombs Minesweeper::generateBombs() {
  Bombs generatedBombs;
  generatedBombs.reserve(bombsAmount_);

  while (generatedBombs.size() < bombsAmount_) {
    int first = generator_->getRandom();
    int second = generator_->getRandom();
    generatedBombs.emplace_back(std::pair<int, int>(first, second));
    deleteBombDuplication(generatedBombs);
  }
  return generatedBombs;
}

void Minesweeper::setBombsAtBoard(Bombs& generatedBombs) {
  for (int i = 0; i < generatedBombs.size(); i++) {
    gameboard_.setBombAt(generatedBombs[i].first, generatedBombs[i].second);
  }
}

void Minesweeper::generateBoard() {
  Bombs bombs = generateBombs();
  setBombsAtBoard(bombs);
}

void Minesweeper::executeUserCommand() {
    std::tuple<char, int, int> commandParameter = player_->makeMove();
    
    switch (std::get<0>(commandParameter))
    {
    case CHOOSE:
        gameboard_.uncoverOneField(std::get<1>(commandParameter), std::get<2>(commandParameter));
        if(gameboard_.getFieldAt(std::get<1>(commandParameter), std::get<2>(commandParameter)).bombility == Bombility::mined){
            gameStatus_ = GameStatus::gameOver;
            gameboard_.uncoverAllFields(); 
        } else {
            if(gameboard_.countLeftFields() == bombsAmount_){
                gameStatus_ = GameStatus::win;
                gameboard_.uncoverAllFields();
            }
        }
        break;
    case FLAG:
        gameboard_.flagField(std::get<1>(commandParameter), std::get<2>(commandParameter));
        break;
    case UNFLAG:
        gameboard_.unflagField(std::get<1>(commandParameter), std::get<2>(commandParameter));
        break;
    default:
        break;
    }
}

void Minesweeper::play(){
    StdViewer viewer;
    generateBoard();
    viewer.drawBoard(gameboard_);

    while(getGameStatus() == GameStatus::ongoing) {
        executeUserCommand();
        viewer.drawBoard(gameboard_);
    }

    if(getGameStatus() == GameStatus::win) {
        viewer.printWin();
    } 
    if(getGameStatus() == GameStatus::gameOver) {
        viewer.printLose();
    }
    
}