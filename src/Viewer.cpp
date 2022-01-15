#include "../inc/Viewer.hpp"

void StdViewer::drawBoard(const Gameboard& gameboard) {
  for (int i = 0; i < gameboard.getWidth(); i++) {
    for (int j = 0; j < gameboard.getHeight(); j++) {
      if (gameboard.getFieldAt(i, j).visibility == Visibility::covered) {
        if (gameboard.getFieldAt(i, j).flagability == Flagability::marked) {
          std::cout << kFlagged;
        } else {
          std::cout << kCover;
        }
      } else {
        if (gameboard.getFieldAt(i, j).bombility == Bombility::mined) {
          std::cout << kMined;
        } else {
          if (gameboard.isFieldAdjacentToBomb(i, j)) {
            std::cout << " " << gameboard.countAdjacentBombAt(i, j);
          } else {
            std::cout << kUncover;
          }
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::this_thread::sleep_for(std::chrono::microseconds(10000));
}

void StdViewer::printWin() {
  std::cout << "Congratulation! You won!" << std::endl;
}

void StdViewer::printLose() { std::cout << "You lose! Try again" << std::endl; }
