#pragma once

#include <memory>

enum class Visibility { covered, uncovered };
enum class Bombility { empty, mined };
enum class Flagability { unmarked, marked };

struct Field {
  Visibility visibility{Visibility::covered};
  Bombility bombility{Bombility::empty};
  Flagability flagability{Flagability::unmarked};
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
  void setBombAt(const int x, const int y);
  void uncoverAllFields();
  void uncoverOneField(const int x, const int y);
  void flagField(const int x, const int y);
  void unflagField(const int x, const int y);
  const Field& getFieldAt(const int row, const int column) const;
  Field& getFieldAt(const int row, const int column);
  int countLeftFields();

 private:
  void uncoverOneFieldIfPossible(const int x, const int y);

  Board board_;
};
