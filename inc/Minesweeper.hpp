#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../inc/Gameboard.hpp"
#include "../inc/PlayerInput.hpp"
#include "../inc/RandomGenerator.hpp"
#include "../inc/Viewer.hpp"

const std::string kPrompt{"> "};

using PlayerInputPtr = std::shared_ptr<PlayerInputI>;
using RandomRangeGeneratorPtr = std::shared_ptr<RandomRangeGeneratorI>;
using Bombs = std::vector<std::pair<int, int>>;

enum class GameStatus { ongoing, gameOver, win };

class Minesweeper {
 public:
  Minesweeper(PlayerInputPtr playerInput, RandomRangeGeneratorPtr generator);
  void generateBoard();
  const Gameboard& getBoard() const { return gameboard_; };
  void play();
  void executeUserCommand();
  const GameStatus& getGameStatus() const { return gameStatus_; };

 private:
  Bombs generateBombs();
  void setBombsAtBoard(Bombs& generatedBombs);
  PlayerInputPtr player_;
  RandomRangeGeneratorPtr generator_;
  Gameboard gameboard_;
  int bombsAmount_{10};
  GameStatus gameStatus_{GameStatus::ongoing};
};
