#pragma once

#include <cassert>
#include <cstdlib>
#include <ctime>

class RandomRangeGeneratorI {
 public:
  virtual int getRandom() = 0;
  virtual ~RandomRangeGeneratorI() {}
};

class StdRandomRangeGenerator : public RandomRangeGeneratorI {
 public:
  StdRandomRangeGenerator(int lower_boundary, int upper_boundary);
  int getRandom() override;
  static void setSeedOnlyOnce();

 private:
  static void setSeed();
  int lower_boundary_;
  int upper_boundary_;
};
