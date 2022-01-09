#include "../inc/PlayerInput.hpp"

#include <iostream>

std::tuple<char, int, int> StdPlayerInput::makeMove() {
  char command;
  int x, y;
  std::cin >> command >> x >> y;
  return std::make_tuple(command, x, y);
}
