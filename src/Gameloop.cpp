#include "../inc/Minesweeper.hpp"

int main() {
  Minesweeper minesweeper(
      std::make_shared<StdPlayerInput>(),
      std::make_shared<StdRandomRangeGenerator>(0, kHeight));
  minesweeper.play();
  return 0;
}
