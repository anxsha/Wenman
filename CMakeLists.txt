cmake_minimum_required(VERSION 3.17)
project(Wenman)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cc src/game.cc src/game.h src/graphical_grid.cc src/graphical_grid.h src/bunny.cc src/bunny.h src/wolf.cc src/wolf.h src/female_wolf.cc src/female_wolf.h src/male_wolf.cc src/male_wolf.h src/square.cc src/square.h)
add_executable(Wenman ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Wenman sfml-system sfml-window sfml-graphics sfml-audio sfml-network)