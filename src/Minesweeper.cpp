#include "../inc/Minesweeper.hpp"

#include <iostream>

Minesweeper::Minesweeper(PlayerInputPtr playerInput,
                         RandomRangeGeneratorPtr generator)
    : player_(playerInput), generator_(generator) {}

bool isGeneratedPairNew(std::pair<int, int> potentialBomb,
                        Bombs& generatedBombs) {
  for (const auto& bomb : generatedBombs) {
    if (bomb.first == potentialBomb.first &&
        bomb.second == potentialBomb.second) {
      return false;
    }
  }
  return true;
}

Bombs Minesweeper::generateBombs() {
  Bombs generatedBombs;
  generatedBombs.reserve(bombsAmount_);

  while (generatedBombs.size() < bombsAmount_) {
    int first = generator_->getRandom();
    int second = generator_->getRandom();
    if (isGeneratedPairNew(std::pair<int, int>(first, second),
                           generatedBombs)) {
      generatedBombs.emplace_back(std::pair<int, int>(first, second));
    }
  }
  return generatedBombs;
}

void Minesweeper::setBombsAtBoard(Bombs& generatedBombs) {
  for (const auto& bomb : generatedBombs) {
    gameboard_.setBombAt(bomb.first, bomb.second);
  }
}

void Minesweeper::generateBoard() {
  Bombs bombs = generateBombs();
  setBombsAtBoard(bombs);
}

void Minesweeper::executeUserCommand() {
  std::tuple<char, int, int> commandParameter = player_->makeMove();

  int position_x = std::get<1>(commandParameter);
  int position_y = std::get<2>(commandParameter);

  switch (std::get<0>(commandParameter)) {
    case kChoose:
      if (gameboard_.getFieldAt(position_x, position_y).flagability ==
              Flagability::marked ||
          gameboard_.getFieldAt(position_x, position_y).visibility ==
              Visibility::uncovered) {
        return;
      }
      gameboard_.uncoverOneField(position_x, position_y);
      if (gameboard_.getFieldAt(position_x, position_y).bombility ==
          Bombility::mined) {
        gameStatus_ = GameStatus::gameOver;
        gameboard_.uncoverAllFields();
      } else {
        if (gameboard_.countLeftFields() == bombsAmount_) {
          gameStatus_ = GameStatus::win;
          gameboard_.uncoverAllFields();
        }
      }
      break;
    case kFlag:
      gameboard_.flagField(position_x, position_y);
      break;
    case kUnflag:
      gameboard_.unflagField(position_x, position_y);
      break;
    default:
      std::cout
          << "Incorrect command. Should be: action position_x position_y.\n"
          << std::endl;
      break;
  }
}

void Minesweeper::play() {
  std::cout << "\nWelcome in Minesweeper!\n To choose a field type: action "
               "position_x position y\n"
            << std::endl;

  StdViewer viewer;
  generateBoard();
  viewer.drawBoard(gameboard_);

  while (getGameStatus() == GameStatus::ongoing) {
    std::cout << kPrompt;
    executeUserCommand();
    viewer.drawBoard(gameboard_);
  }

  if (getGameStatus() == GameStatus::win) {
    viewer.printWin();
  }
  if (getGameStatus() == GameStatus::gameOver) {
    viewer.printLose();
  }
}
