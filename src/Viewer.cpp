#include "../inc/Viewer.hpp"

void StdViewer::drawBoard(const Gameboard& gameboard) {
  for (int i = 0; i < gameboard.getWidth(); i++) {
    for (int j = 0; j < gameboard.getHeight(); j++) {
      if (gameboard.getFieldAt(i, j).flagability == Flagability::marked) {
        std::cout << " F";
      } else if (gameboard.getFieldAt(i, j).visibility == Visibility::covered) {
        std::cout << " X";
      } else {
        if (gameboard.isFieldAdjacentToBomb(i, j))
          std::cout << " " << gameboard.countAdjacentBombAt(i, j);
        else
          std::cout << " O";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  usleep(10000);
}