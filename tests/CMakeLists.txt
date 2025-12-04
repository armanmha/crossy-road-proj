cmake_minimum_required(VERSION 3.20)

project(CS100FinalProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
add_subdirectory(googletest)

add_executable(runLeaderboardTests
    leaderboardTest.cpp
    ../src/Leaderboard.cpp
    ../src/Screen.cpp
)

add_executable(runMenuTests
    menuTest.cpp
    ../src/Menu.cpp
    ../src/Screen.cpp
    ../src/Leaderboard.cpp
    ../src/Game.cpp
    ../src/Board.cpp
    ../src/Player.cpp
    ../src/GameplayObjects.cpp
    ../src/Lane.cpp
    ../src/Vehicle.cpp
    ../src/GameOverScreen.cpp
    ../src/PauseScreen.cpp
)

add_executable(runLaneTests
    laneTest.cpp
    ../src/Lane.cpp
    ../src/Vehicle.cpp
    ../src/GameplayObjects.cpp
)

add_executable(runBoardTests
    boardTest.cpp
    ../src/Board.cpp
    ../src/Lane.cpp
    ../src/Vehicle.cpp
    ../src/GameplayObjects.cpp
)

add_executable(runGameTests
    gameTest.cpp
    ../src/Game.cpp
    ../src/Menu.cpp
    ../src/Screen.cpp
    ../src/Board.cpp
    ../src/Player.cpp
    ../src/GameplayObjects.cpp
    ../src/Lane.cpp
    ../src/Vehicle.cpp
    ../src/GameOverScreen.cpp
    ../src/PauseScreen.cpp
    ../src/Leaderboard.cpp
)

add_executable(runGameOverTests
    gameOverTest.cpp
    ../src/GameOverScreen.cpp
    ../src/PauseScreen.cpp
    ../src/Screen.cpp
    ../src/Board.cpp
    ../src/Player.cpp
    ../src/GameplayObjects.cpp
    ../src/Lane.cpp
    ../src/Vehicle.cpp
    ../src/Leaderboard.cpp
    ../src/Game.cpp
    ../src/Menu.cpp
)

target_link_libraries(runLeaderboardTests gtest gtest_main)
target_link_libraries(runMenuTests gtest gtest_main)
target_link_libraries(runLaneTests gtest gtest_main)
target_link_libraries(runBoardTests gtest gtest_main)
target_link_libraries(runGameTests gtest gtest_main)
target_link_libraries(runGameOverTests gtest gtest_main)