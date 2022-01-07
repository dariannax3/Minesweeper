#include "../inc/RandomGenerator.hpp"

void StdRandomRangeGenerator::setSeed() {
  static bool once = true;
  if (once) std::srand(std::time(NULL));
  once = false;
}

StdRandomRangeGenerator::StdRandomRangeGenerator(int lower_boundary,
                                                 int upper_boundary)
    : lower_boundary_(lower_boundary), upper_boundary_(upper_boundary) {
  assert(lower_boundary <= upper_boundary);
  StdRandomRangeGenerator::setSeed();
}

int StdRandomRangeGenerator::getRandom() {
  return (std::rand() % (upper_boundary_ - lower_boundary_)) + lower_boundary_;
}
