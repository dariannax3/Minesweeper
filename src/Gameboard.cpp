#include "../inc/Gameboard.hpp"

#include <iostream>

void Gameboard::uncoverAllFields() {
  for (auto& row : board_) {
    for (auto& field : row) {
      field.visibility = Visibility::uncovered;
    }
  }
}

bool Gameboard::isFieldInGameboard(const int x, const int y) const {
  return 0 <= x && x < getWidth() && 0 <= y && y < getHeight();
}

bool Gameboard::isFieldMined(const int x, const int y) const {
  return isFieldInGameboard(x, y) &&
         getFieldAt(x, y).bombility == Bombility::mined;
}

bool Gameboard::isFieldAdjacentToBomb(const int x, const int y) const {
  return (isFieldMined(x + 1, y) || isFieldMined(x - 1, y) ||
          isFieldMined(x, y + 1) || isFieldMined(x, y - 1) ||
          isFieldMined(x + 1, y - 1) || isFieldMined(x + 1, y + 1) ||
          isFieldMined(x - 1, y - 1) || isFieldMined(x - 1, y + 1));
}

void Gameboard::uncoverOneFieldIfPossible(const int x, const int y) {
  if (isFieldInGameboard(x, y) &&
      getFieldAt(x, y).visibility == Visibility::covered &&
      getFieldAt(x, y).flagability == Flagability::unmarked)
    uncoverOneField(x, y);
}

void Gameboard::uncoverOneField(const int x, const int y) {
  if (isFieldAdjacentToBomb(x, y)) {
    getFieldAt(x, y).visibility = Visibility::uncovered;
    return;
  }

  getFieldAt(x, y).visibility = Visibility::uncovered;

  uncoverOneFieldIfPossible(x - 1, y - 1);
  uncoverOneFieldIfPossible(x - 1, y);
  uncoverOneFieldIfPossible(x - 1, y + 1);
  uncoverOneFieldIfPossible(x + 1, y - 1);
  uncoverOneFieldIfPossible(x + 1, y);
  uncoverOneFieldIfPossible(x + 1, y + 1);
  uncoverOneFieldIfPossible(x, y - 1);
  uncoverOneFieldIfPossible(x, y);
  uncoverOneFieldIfPossible(x, y + 1);
}

int Gameboard::countAdjacentBombAt(const int x, const int y) const {
  int counter{0};

  if (isFieldMined(x + 1, y)) {
    counter++;
  }
  if (isFieldMined(x - 1, y)) {
    counter++;
  }
  if (isFieldMined(x, y + 1)) {
    counter++;
  }
  if (isFieldMined(x, y - 1)) {
    counter++;
  }
  if (isFieldMined(x + 1, y - 1)) {
    counter++;
  }
  if (isFieldMined(x + 1, y + 1)) {
    counter++;
  }
  if (isFieldMined(x - 1, y - 1)) {
    counter++;
  }
  if (isFieldMined(x - 1, y + 1)) {
    counter++;
  }
  return counter;
}

int Gameboard::getWidth() const { return board_[0].size(); }

int Gameboard::getHeight() const { return board_.size(); }

const Field& Gameboard::getFieldAt(int row, int column) const {
  return board_[row][column];
}

Field& Gameboard::getFieldAt(int row, int column) {
  return board_[row][column];
}

void Gameboard::setBombAt(const int x, const int y) {
  Field& field = getFieldAt(x, y);
  field.bombility = Bombility::mined;
}

void Gameboard::flagField(const int x, const int y) {
  Field& field = getFieldAt(x, y);
  field.flagability = Flagability::marked;
};

void Gameboard::unflagField(const int x, const int y) {
  Field& field = getFieldAt(x, y);
  if (field.flagability != Flagability::marked) {
    std::cout << "Field is not flagged" << std::endl;
  } else {
    field.flagability = Flagability::unmarked;
  }
};

int Gameboard::countLeftFields() {
  int counter{0};
  for (auto& row : board_) {
    for (auto& field : row) {
      if (field.visibility == Visibility::covered) {
        counter++;
      }
    }
  }
  return counter;
}
