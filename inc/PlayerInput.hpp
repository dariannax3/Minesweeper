#pragma once

#include <memory>
#include <tuple>

constexpr char CHOOSE = 'c';
constexpr char FLAG = 'f';
constexpr char UNFLAG = 'u';

class PlayerInputI {
 public:
  virtual ~PlayerInputI() {}
  virtual std::tuple<char, int, int> makeMove() = 0;
};

class StdPlayerInput : public PlayerInputI {
 public:
  std::tuple<char, int, int> makeMove() override;
};