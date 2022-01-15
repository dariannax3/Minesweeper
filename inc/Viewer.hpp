#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "Gameboard.hpp"

const std::string kCover{" X"};
const std::string kFlagged{" F"};
const std::string kUncover{" O"};
const std::string kMined{" M"};

class ViewerI {
 public:
  virtual void drawBoard(const Gameboard& gameboard) = 0;
  virtual void printWin() = 0;
  virtual void printLose() = 0;
  virtual ~ViewerI() {}
};

class StdViewer : public ViewerI {
 public:
  void drawBoard(const Gameboard& gameboard) override;
  void printWin() override;
  void printLose() override;
};
