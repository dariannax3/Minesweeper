#pragma once

#include <memory>
#include <tuple>

class PlayerInputI {
public:
    virtual ~PlayerInputI() {}
    virtual std::tuple<char, int, int> makeMove() = 0;
};