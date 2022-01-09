#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../inc/Minesweeper.hpp"
#include "../inc/PlayerInput.hpp"
#include "../inc/RandomGenerator.hpp"
#include "../inc/Viewer.hpp"

using ::testing::AtLeast;
using ::testing::Return;

class MockPlayerInput : public PlayerInputI {
 public:
  MOCK_METHOD((std::tuple<char, int, int>), makeMove, (), (override));
};

class MockRandomRangeGenerator : public RandomRangeGeneratorI {
 public:
  MOCK_METHOD(int, getRandom, (), (override));
};

TEST(MinesweeperTest, MakeMovesTest) {
  MockPlayerInput player;
  EXPECT_CALL(player, makeMove())
      .Times(AtLeast(2))
      .WillOnce(Return(std::make_tuple<char, int, int>('w', 1, 1)))
      .WillOnce(Return(std::make_tuple<char, int, int>('w', 1, 1)));
  EXPECT_EQ(player.makeMove(), (std::make_tuple<char, int, int>('w', 1, 1)));
  auto something = player.makeMove();
}

TEST(MinesweeperTest, givenBoardWhenGenerateBoardThanShouldGenerateTenBombs) {
  Minesweeper minesweeper(std::make_shared<MockPlayerInput>(),
                          std::make_shared<StdRandomRangeGenerator>(0, 8));
  minesweeper.generateBoard();
  const Gameboard& board = minesweeper.getBoard();

  int bombsCounter{0};

  for (int i = 0; i < board.getHeight(); i++) {
    for (int j = 0; j < board.getWidth(); j++) {
      if (board.getFieldAt(i, j).bombility == Bombility::mined) {
        bombsCounter++;
      }
    }
  }
  EXPECT_EQ(bombsCounter, 10);
}

TEST(MinesweeperTest,
    givenBombAtLeftTopCornerWhenPlayerClicksAdjacentFieldAndBombFieldThenGameStatusIsGameOver) {
  std::shared_ptr<MockPlayerInput> fakePlayerInput(std::make_shared<MockPlayerInput>());
  std::shared_ptr<MockRandomRangeGenerator> fakeGenerator(std::make_shared<MockRandomRangeGenerator>());

  Minesweeper minesweeper(fakePlayerInput, fakeGenerator);
  EXPECT_CALL(*fakeGenerator, getRandom())
      .Times(20)
      .WillOnce(Return(0))
      .WillOnce(Return(0))
      .WillOnce(Return(7))
      .WillOnce(Return(7))
      .WillOnce(Return(7))
      .WillOnce(Return(6))
      .WillOnce(Return(7))
      .WillOnce(Return(5))
      .WillOnce(Return(7))
      .WillOnce(Return(4))
      .WillOnce(Return(7))
      .WillOnce(Return(3))
      .WillOnce(Return(7))
      .WillOnce(Return(2))
      .WillOnce(Return(7))
      .WillOnce(Return(1))
      .WillOnce(Return(7))
      .WillOnce(Return(0))
      .WillOnce(Return(6))
      .WillOnce(Return(0));
  minesweeper.generateBoard();

  EXPECT_CALL(*fakePlayerInput, makeMove())
      .Times(2)
      .WillOnce(Return((std::make_tuple('c', 0, 1))))
      .WillOnce(Return((std::make_tuple('c', 0, 0))));

  minesweeper.executeUserCommand();
  EXPECT_EQ(minesweeper.getGameStatus(), GameStatus::ongoing);
  minesweeper.executeUserCommand();
  EXPECT_EQ(minesweeper.getGameStatus(), GameStatus::gameOver);

  const Gameboard& gameboard = minesweeper.getBoard();

  for (int row = 0; row < gameboard.getHeight(); row++) {
    for (int column = 0; column < gameboard.getWidth(); column++) {
      EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
    }
  }
}

TEST(MinesweeperTest,
    givenBombAtLeftTopCornerWhenPlayerClicksAdjacentFieldAndEmptyFieldThenGameStatusWin) {
  std::shared_ptr<MockPlayerInput> fakePlayerInput(std::make_shared<MockPlayerInput>());
  std::shared_ptr<MockRandomRangeGenerator> fakeGenerator(std::make_shared<MockRandomRangeGenerator>());

  Minesweeper minesweeper(fakePlayerInput, fakeGenerator);
  EXPECT_CALL(*fakeGenerator, getRandom())
      .Times(20)
      .WillOnce(Return(0))
      .WillOnce(Return(0))
      .WillOnce(Return(7))
      .WillOnce(Return(7))
      .WillOnce(Return(7))
      .WillOnce(Return(6))
      .WillOnce(Return(7))
      .WillOnce(Return(5))
      .WillOnce(Return(7))
      .WillOnce(Return(4))
      .WillOnce(Return(7))
      .WillOnce(Return(3))
      .WillOnce(Return(7))
      .WillOnce(Return(2))
      .WillOnce(Return(7))
      .WillOnce(Return(1))
      .WillOnce(Return(7))
      .WillOnce(Return(0))
      .WillOnce(Return(6))
      .WillOnce(Return(0));
  minesweeper.generateBoard();

  EXPECT_CALL(*fakePlayerInput, makeMove())
      .Times(2)
      .WillOnce(Return((std::make_tuple('c', 0, 1))))
      .WillOnce(Return((std::make_tuple('c', 0, 2))));

  minesweeper.executeUserCommand();
  EXPECT_EQ(minesweeper.getGameStatus(), GameStatus::ongoing);
  minesweeper.executeUserCommand();
  EXPECT_EQ(minesweeper.getGameStatus(), GameStatus::win);

  const Gameboard& gameboard = minesweeper.getBoard();

  for (int row = 0; row < gameboard.getHeight(); row++) {
    for (int column = 0; column < gameboard.getWidth(); column++) {
      EXPECT_EQ(gameboard.getFieldAt(row, column).visibility, Visibility::uncovered);
    }
  }
}