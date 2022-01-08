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

TEST(GameboardTest, GivenCoveredBoardWhenUncoverAllFieldsThanAllFieldsVisibilityStatusShouldBeUncover) {
    //Given
    Gameboard gameboard;
    //When
    gameboard.uncoverAllFields();
    //Then
    for (int row = 0; row < gameboard.getHeight(); row++) {
        for (int column = 0; column < gameboard.getWidth(); column++) {
            EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
        }
    }
}
TEST(GameboardTest, GivenBoardWithTwoBombsThenCheckIfIsFieldAdjacentToBombShouldReturnTrueInformation) {
    Gameboard gameboard;

    gameboard.setBomb(0, 0);
    EXPECT_EQ(gameboard.getFieldAt(0, 0).bombility, Bombility::mined);
    EXPECT_TRUE(gameboard.isFieldAdjacentToBomb(1, 1));
    EXPECT_FALSE(gameboard.isFieldAdjacentToBomb(1, 2));

    gameboard.setBomb(3, 2);
    EXPECT_TRUE(gameboard.isFieldAdjacentToBomb(2, 1));
}

// TEST(GameboardTest, GivenOneBombThanUncoverOneFieldShouldUncoverAllEmpltyFields) {
//     Gameboard gameboard;
//     gameboard.setBomb(0, 0);
//     gameboard.uncoverOneField(1, 2);

//     EXPECT_EQ(gameboard.countAdjacentBombAt(0,1), 1);
//     EXPECT_EQ(gameboard.countAdjacentBombAt(1,1), 1);
//     EXPECT_EQ(gameboard.countAdjacentBombAt(1,0), 1);
//     EXPECT_EQ(gameboard.countAdjacentBombAt(1,2), 0);
//     EXPECT_EQ(gameboard.getFieldAt(1, 2).visibility, Visibility::uncovered);
//     EXPECT_EQ(gameboard.getFieldAt(0, 1).visibility, Visibility::uncovered);
//     EXPECT_EQ(gameboard.getFieldAt(1, 1).visibility, Visibility::uncovered);

//     int row = 0;
//     for (int column = 2; column < gameboard.getWidth(); column++) {
//         EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
//     }

//     row = 1;
//     for (int column = 3; column < gameboard.getWidth(); column++) {
//         EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
//     }
    
//     for (int row = 2; row < gameboard.getHeight(); row++) {
//         for (int column = 0; column < gameboard.getWidth(); column++) {
//             EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
//         }
//     }
// }

TEST(GameboardTest, GivenThreeBombThanUncoverOneFieldShouldUncoverAllPossibleEmpltyFields)
{
    Gameboard gameboard;
    gameboard.setBomb(2, 1);
    gameboard.setBomb(3, 3);
    gameboard.setBomb(2, 6);
    gameboard.uncoverOneField(0, 4);

    EXPECT_EQ(gameboard.getFieldAt(2, 1).visibility, Visibility::covered);
    EXPECT_EQ(gameboard.getFieldAt(3, 2).visibility, Visibility::covered);
    EXPECT_EQ(gameboard.getFieldAt(4, 4).visibility, Visibility::covered);

    
    // int row = 0;
    // for (int column = 0; column < gameboard.getWidth(); column++) {
    //     EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
    // }

    // row = 1;
    // for (int column = 0; column < gameboard.getWidth(); column++) {
    //     EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
    // }

    // row = 5;
    // for (int column = 0; column < gameboard.getWidth(); column++) {
    //     EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::covered);
    // }




}
