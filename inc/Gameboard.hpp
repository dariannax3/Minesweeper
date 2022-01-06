#pragma once
#include <memory>
#include "RandomGeneratorI.hpp"

using RandomGeneratorPtr = std::shared_ptr<RandomGeneratorI>;

class Gameboard {
public:
private:
    std::shared_ptr<RandomGeneratorI> generator;
};