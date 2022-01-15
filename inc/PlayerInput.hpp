#pragma once

#include <memory>
#include <tuple>

constexpr char kChoose = 'c';
constexpr char kFlag = 'f';
constexpr char kUnflag = 'u';

class PlayerInputI {
 public:
  virtual ~PlayerInputI() {}
  virtual std::tuple<char, int, int> makeMove() = 0;
};

class StdPlayerInput : public PlayerInputI {
 public:
  std::tuple<char, int, int> makeMove() override;
};
