#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../inc/Minesweeper.hpp"
#include "../inc/PlayerInputI.hpp"

using ::testing::AtLeast;
using ::testing::Return;

TEST(MinesweeperTest, TrueIsTrue) {
    ASSERT_EQ(true, true);
}

class MockPlayerInput : public PlayerInputI {
public:
    MOCK_METHOD((std::tuple<char, int, int>), makeMove, (), (override));
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