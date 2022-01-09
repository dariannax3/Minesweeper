cmake_minimum_required(VERSION 3.14)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(
  minesweeper-lib
  src/Minesweeper.cpp
  src/Gameboard.cpp
  src/Viewer.cpp
  src/RandomGenerator.cpp
  src/PlayerInput.cpp
)

add_executable(
  minesweeper-uts
  tests/GameboardTest.cpp
  tests/MinesweeperTest.cpp
  tests/RandomGeneratorTest.cpp
)

add_executable(
  minesweeper
  src/Gameloop.cpp
)

target_link_libraries(
  minesweeper-uts
  minesweeper-lib
  gmock_main
)

target_link_libraries(
  minesweeper
  minesweeper-lib
)

include(GoogleTest)
gtest_discover_tests(minesweeper-uts)