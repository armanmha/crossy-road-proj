cmake_minimum_required(VERSION 3.2)

project(CS100FinalProject)

# Put all binaries go in bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Header files live in include
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${LIBRARY_OUTPUT_PATH})

# include(GoogleTest)
include_directories(
  ${CMAKE_SOURCE_DIR}/test/lib/googletest/include/
)

add_executable(CS100FinalProject
    src/main.cpp
    src/Menu.cpp
    src/Screen.cpp
    src/Leaderboard.cpp
    src/Game.cpp
    src/GameplayObjects.cpp
    src/Board.cpp
    src/Player.cpp
)

# BUILD TESTS
add_subdirectory(tests)

