#pragma once
#include <unistd.h>

#include <chrono>
#include <iostream>

#include "Gameboard.hpp"

class ViewerI {
 public:
  virtual void drawBoard(const Gameboard& gameboard) = 0;
  virtual ~ViewerI() {}
};

class StdViewer : public ViewerI {
 public:
  void drawBoard(const Gameboard& gameboard) override;
};
