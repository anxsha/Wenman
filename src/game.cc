//
// Created by Jakub Molek on 22/10/2020.
//
#include <iostream>

#include "game.h"

std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index) {
  std::vector<int> v{};
  int row = index / size_x;
  int col = index % size_x;

  // find upper-left neighbour
  if (col > 0 && row > 0) {
    int upper_left = (row - 1) * size_x + (col - 1);
    v.push_back(upper_left);
  }
  // find mid-left neighbour
  if (col > 0) {
    int mid_left = row * size_x + (col - 1);
    v.push_back(mid_left);
  }
  // find lower-left neighbour
  if (col > 0 && row < (size_y - 1)) {
    int lower_left = (row + 1) * size_x + (col - 1);
    v.push_back(lower_left);
  }
  // find upper neighbour
  if (row > 0) {
    int upper = (row - 1) * size_x + col;
    v.push_back(upper);
  }
  // find lower neighbour
  if (row < (size_y - 1)) {
    int lower = (row + 1) * size_x + col;
    v.push_back(lower);
  }
  // find upper-right neighbour
  if (row > 0 && col < (size_x - 1)) {
    int upper_right = (row - 1) * size_x + (col + 1);
    v.push_back(upper_right);
  }
  // find mid-right neighbour
  if (col < (size_x - 1)) {
    int mid_right = row * size_x + (col + 1);
    v.push_back(mid_right);
  }
  // find lower-right neighbour
  if (row < (size_y - 1)) {
    int lower_right = (row + 1) * size_x + (col + 1);
    v.push_back(lower_right);
  }
  return v;
}

Square::Square(std::vector<Square>& v) {
  bunnies_ = 0;
  male_wolves_ = 0;
  female_wolves_ = 0;
  vector_index_ = distance(v.begin(), v.end());
}

int Square::bunnies() const { return bunnies_; }
int Square::male_wolves() const { return male_wolves_; }
int Square::female_wolves() const { return female_wolves_; }
int Square::vector_index() const { return vector_index_; }

Game::Game(int columns, int rows) {
  map_tiles = std::vector<int>(rows * columns);
  for (int i = 0; i < map_tiles.size(); ++i) {
    squares_vector.emplace_back(Square(squares_vector));
  }
  if (!font.loadFromFile("../resources/font.ttf")) {
    std::exit(1);
  }
  if (!square_map.Load("../resources/tileset1.png", sf::Vector2u(60, 60), map_tiles, columns, rows)) {
    std::exit(1);
  }
}
void Game::Run() {
  sf::RenderWindow window(sf::VideoMode(1402, 840), "Wenman");
  window.setFramerateLimit(20);
  while (window.isOpen()) {
    sf::Event event{};

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(square_map);
    window.display();
  }
}


