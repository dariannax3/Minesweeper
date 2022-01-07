#pragma once

#include <memory>
#include <string>
#include <tuple>

<<<<<<< HEAD
#include "../inc/PlayerInputI.hpp"
=======
#include "../inc/PlayerInput.hpp"
>>>>>>> Add RandomGenerator

using PlayerPtr = std::shared_ptr<PlayerInputI>;

class Minesweeper {
 public:
  std::string sayHello();

 private:
  PlayerPtr player;
};