#pragma once
#include <memory>

#include "RandomGeneratorI.hpp"

using RandomGeneratorPtr = std::shared_ptr<RandomGeneratorI>;

enum class Visibility { covered, uncovered };
// don't ask
enum class Bombility { empty, mined };

// don't ask again
enum class Flagability { unmarked, marked };

struct Field {
  Visibility visibility = Visibility::covered;
  Bombility bombility = Bombility::empty;
  Flagability flagability = Flagability::unmarked;
};

using Board = std::array<std::array<Field, 8>, 8>;

class Gameboard {
 public:
  int getWidth() const;
  int getHeight() const;
  int countAdjacentBombAt(const int x, const int y) const;
  bool isFieldAdjacentToBomb(const int x, const int y) const;
  bool isFieldInGameboard(const int x, const int y) const;
  bool isFieldMined(const int x, const int y) const;
  void setBomb(const int x, const int y);
  void uncoverAllFields();
  void uncoverOneField(const int x, const int y);
  void flagField(const int x, const int y);
  const Field& getFieldAt(const int row, const int column) const;
  Field& getFieldAt(const int row, const int column);

 private:
  void uncoverOneFieldIfPossible(const int x, const int y);

  std::shared_ptr<RandomGeneratorI> generator;
  Board board_;
};