#pragma once
#include <memory>
#include "RandomGeneratorI.hpp"

using RandomGeneratorPtr = std::shared_ptr<RandomGeneratorI>;

enum class Visibility { covered,
                        uncovered };
// don't ask
enum class Bombility { empty,
                       mined };

struct Field {
    Visibility visibility = Visibility::covered;
    Bombility bombility = Bombility::empty;
};

using Board = std::array<std::array<Field, 8>, 8>;

class Gameboard {
public:
    void uncoverAllFields();
    void uncoverOneField(const int x, const int y);
    int getWidth() const;
    int getHeight() const;
    void setBomb(const int x, const int y);
    Field& getFieldAt(const int row, const int column);
    bool isFieldAdjacentToBomb(const int x, const int y);
    bool isFieldInGameboard(const int x, const int y);
    bool isFieldMined(const int x, const int y);
    int countAdjacentBombAt(const int x, const int y);
    void printBoardVisibility();

private:
    void uncoverOneFieldIfPossible(const int x, const int y);

    std::shared_ptr<RandomGeneratorI> generator;
    Board board_;
};