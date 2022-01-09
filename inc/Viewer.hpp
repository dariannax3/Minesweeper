#pragma once
#include <chrono>
#include <iostream>
#include <thread>

#include "Gameboard.hpp"

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
  void printWin();
  void printLose();
};
