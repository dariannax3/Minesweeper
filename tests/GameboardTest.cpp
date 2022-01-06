#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../inc/Gameboard.hpp"

using ::testing::Return;

TEST(GameboardTest, TrueIsTrue) {
    ASSERT_EQ(true, true);
}

class MockRandomGenerator : public RandomGeneratorI {
public:
    MOCK_METHOD(int, getRandom, (), (override));
};

TEST(RandomGeneratorTest, getRandomTest) {
    MockRandomGenerator generator;
    EXPECT_CALL(generator, getRandom())
        .Times(1)
        .WillOnce(Return(13));

    EXPECT_EQ(generator.getRandom(), 13);
}