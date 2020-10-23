cmake_minimum_required(VERSION 3.17)
project(Wenman)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cc src/animals.cc src/animals.h src/game.cc src/game.h src/graphical_grid.cc src/graphical_grid.h)
add_executable(Wenman ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Wenman sfml-system sfml-window sfml-graphics sfml-audio sfml-network)