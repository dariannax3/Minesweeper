#include "../inc/RandomGenerator.hpp"

void StdRandomRangeGenerator::setSeedOnlyOnce() {
  static bool once = true;
  if (once)
    std::srand(std::time(NULL));
  once = false;
}

StdRandomRangeGenerator::StdRandomRangeGenerator(int lower_boundary,
                                                 int upper_boundary)
    : lower_boundary_(lower_boundary), upper_boundary_(upper_boundary) {
  assert(lower_boundary <= upper_boundary);
  setSeedOnlyOnce();
}

int StdRandomRangeGenerator::getRandom() {
  return (std::rand() % (upper_boundary_ - lower_boundary_)) + lower_boundary_;
}
