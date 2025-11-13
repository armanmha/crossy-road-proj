cmake_minimum_required(VERSION 3.20)

project(CS100FinalProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
add_subdirectory(googletest)

add_executable(runLeaderboardTests
    leaderboardTest.cpp
    ../src/Leaderboard.cpp
)


target_link_libraries(runLeaderboardTests gtest gtest_main)