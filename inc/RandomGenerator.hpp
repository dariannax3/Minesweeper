#pragma once

#include <cassert>
#include <cstdlib>
#include <ctime>

class RandomFromRangeGeneratorI {
 public:
  virtual int getRandom() = 0;
  virtual ~RandomFromRangeGeneratorI() {}
};

class StdRandomRangeGenerator : public RandomFromRangeGeneratorI {
 public:
  StdRandomRangeGenerator(int lower_boundary, int upper_boundary);
  int getRandom() override;

 protected:
  static void setSeed();
  int lower_boundary_;
  int upper_boundary_;
};