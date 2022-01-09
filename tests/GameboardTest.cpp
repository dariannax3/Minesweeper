#include <gtest/gtest.h>

#include "../inc/Gameboard.hpp"
#include "../inc/Viewer.hpp"

class GameboardTestFixture : public ::testing::Test {
 protected:
  Gameboard gameboard;

  void printBoard() {
    StdViewer viewer;
    viewer.drawBoard(gameboard);
  }

  void checkVisibilityOfAllFields(Visibility visibility) {
    for (int row = 0; row < gameboard.getHeight(); row++) {
      for (int column = 0; column < gameboard.getWidth(); column++) {
        EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, visibility);
      }
    }
  }

  void checkVisibilityOfSpecificRowsAndFields(int row_start, int row_end,
                                              int column_start, int column_end,
                                              Visibility visibility) {
    for (int row = row_start; row <= row_end; row++) {
      for (int column = column_start; column <= column_end; column++) {
        EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, visibility);
      }
    }
  }

  void flagEightFieldsToMakeSquare(int x, int y) {
    gameboard.flagField(x - 1, y - 1);
    gameboard.flagField(x - 1, y);
    gameboard.flagField(x - 1, y + 1);
    gameboard.flagField(x + 1, y - 1);
    gameboard.flagField(x + 1, y);
    gameboard.flagField(x + 1, y + 1);
    gameboard.flagField(x, y - 1);
    gameboard.flagField(x, y);
    gameboard.flagField(x, y + 1);
  }
};

TEST_F(
    GameboardTestFixture,
    givenCoveredBoardWhenUncoverAllFieldsThanAllFieldsVisibilityStatusShouldBeUncover) {
  gameboard.uncoverAllFields();
  checkVisibilityOfAllFields(Visibility::uncovered);
}

TEST_F(
    GameboardTestFixture,
    givenBoardWithTwoBombsThenCheckIfIsFieldAdjacentToBombShouldReturnTrueInformation) {
  gameboard.setBombAt(0, 0);
  EXPECT_EQ(gameboard.getFieldAt(0, 0).bombility, Bombility::mined);
  EXPECT_TRUE(gameboard.isFieldAdjacentToBomb(1, 1));
  EXPECT_FALSE(gameboard.isFieldAdjacentToBomb(1, 2));

  gameboard.setBombAt(3, 2);
  EXPECT_TRUE(gameboard.isFieldAdjacentToBomb(2, 1));
}

TEST_F(GameboardTestFixture,
       givenOneBombThanUncoverOneFieldShouldUncoverAllEmpltyFields) {
  gameboard.setBombAt(0, 0);
  gameboard.uncoverOneField(1, 2);

  EXPECT_EQ(gameboard.countAdjacentBombAt(0, 1), 1);
  EXPECT_EQ(gameboard.countAdjacentBombAt(1, 1), 1);
  EXPECT_EQ(gameboard.countAdjacentBombAt(1, 0), 1);
  EXPECT_EQ(gameboard.countAdjacentBombAt(1, 2), 0);

  checkVisibilityOfSpecificRowsAndFields(0, 0, 2, 7, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(1, 7, 0, 7, Visibility::uncovered);
}

TEST_F(GameboardTestFixture,
       givenThreeBombThanUncoverOneFieldShouldUncoverAllPossibleEmpltyFields) {
  gameboard.setBombAt(2, 1);
  gameboard.setBombAt(3, 3);
  gameboard.setBombAt(2, 6);
  gameboard.uncoverOneField(0, 4);

  checkVisibilityOfSpecificRowsAndFields(0, 1, 0, 7, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(1, 1, 2, 5, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(3, 7, 0, 7, Visibility::covered);
}

TEST_F(
    GameboardTestFixture,
    givenBoardWithNoBombsWhenMarkOneFieldWithFlagAndUncoverOneFieldThenAllFieldsAreUncoverInsteadOfFlagOne) {
  gameboard.flagField(1, 1);
  gameboard.uncoverOneField(0, 4);

  EXPECT_TRUE(gameboard.getFieldAt(1, 1).flagability == Flagability::marked);

  checkVisibilityOfSpecificRowsAndFields(0, 0, 0, 7, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(1, 1, 1, 1, Visibility::covered);
  checkVisibilityOfSpecificRowsAndFields(2, 7, 0, 7, Visibility::uncovered);
}

TEST_F(
    GameboardTestFixture,
    givenBoardWithOneBombsWhenMarkOneFieldWithFlagAndUncoverOneFieldThenPossibleFieldsUncover) {
  gameboard.setBombAt(1, 1);
  gameboard.flagField(1, 1);
  gameboard.uncoverOneField(0, 4);

  EXPECT_TRUE(gameboard.getFieldAt(1, 1).flagability == Flagability::marked);

  EXPECT_EQ(gameboard.countAdjacentBombAt(0, 0), 1);
  EXPECT_EQ(gameboard.countAdjacentBombAt(0, 1), 1);

  checkVisibilityOfSpecificRowsAndFields(0, 1, 0, 1, Visibility::covered);
  checkVisibilityOfSpecificRowsAndFields(0, 2, 2, 7, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(2, 7, 0, 7, Visibility::uncovered);
}

TEST_F(
    GameboardTestFixture,
    givenBoardWithEightFlagsFormingSquareWithUncoverFieldInsideWhenClickInUncoverFIeldsThenShouldUncoverOnlyThatField) {
  flagEightFieldsToMakeSquare(2, 5);
  gameboard.uncoverOneField(2, 5);

  checkVisibilityOfSpecificRowsAndFields(0, 1, 0, 7, Visibility::covered);
  checkVisibilityOfSpecificRowsAndFields(2, 2, 0, 4, Visibility::covered);
  checkVisibilityOfSpecificRowsAndFields(2, 2, 5, 5, Visibility::uncovered);
  checkVisibilityOfSpecificRowsAndFields(2, 2, 6, 7, Visibility::covered);
  checkVisibilityOfSpecificRowsAndFields(4, 7, 0, 7, Visibility::covered);

  EXPECT_TRUE(gameboard.getFieldAt(1, 4).flagability == Flagability::marked);
}