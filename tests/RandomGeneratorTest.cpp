#include <gmock/gmock.h>

#include <vector>

#include "../inc/RandomGenerator.hpp"

TEST(RandomRangeGeneratorTest,
     GivenRangeFromZeroToTenExpectRandomFromZeroToTen) {
  StdRandomRangeGenerator randomGenerator(0, 10);
  auto generated = randomGenerator.getRandom();

  EXPECT_LE(0, generated);
  EXPECT_LE(generated, 10);
}

TEST(
    RandomRangeGeneratorTest,
    TwiceGeneratedTenRandomsByDifferentGeneratosShouldHaveAtLeastOneDifferentNumber) {
  StdRandomRangeGenerator randomGenerator1(0, 10);
  std::vector<int> first;
  for (int i = 0; i < 10; i++) {
    first.push_back(randomGenerator1.getRandom());
  }

  StdRandomRangeGenerator randomGenerator2(0, 10);
  std::vector<int> second;
  for (int i = 0; i < 10; i++) {
    second.push_back(randomGenerator2.getRandom());
  }

  bool are_all_same = true;
  for (int i = 0; i < 10; i++) {
    are_all_same = are_all_same && first[i] == second[i];
  }

  EXPECT_FALSE(are_all_same);
}
