#pragma once
#include "Gameboard.hpp"
#include <chrono>
#include <unistd.h>
#include <iostream>

class ViewerI {
public:
   virtual void drawBoard(const Gameboard& gameboard) = 0;
   virtual ~ViewerI(){}
};

class StdViewer : public ViewerI {
public:
    void drawBoard(const Gameboard& gameboard) override;
};
