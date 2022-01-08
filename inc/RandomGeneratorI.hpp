#pragma once

class RandomGeneratorI {
 public:
  virtual int getRandom() = 0;
  virtual ~RandomGeneratorI() {}
};