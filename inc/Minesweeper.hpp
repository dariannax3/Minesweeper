#pragma once
#include <memory>
#include <string>
#include <tuple>
#include "../inc/PlayerInputI.hpp"

using PlayerPtr = std::shared_ptr<PlayerInputI>;

class Minesweeper {
public:
    std::string sayHello();

private:
    PlayerPtr player;
};