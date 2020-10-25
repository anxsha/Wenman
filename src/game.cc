//
// Created by Jakub Molek on 22/10/2020.
//
#include <iostream>
#include <random>

#include "game.h"

Square::Square(std::vector<Square> &v) {
  bunnies_ = 0;
  male_wolves_ = 0;
  female_wolves_ = 0;
  vector_index_ = distance(v.begin(), v.end());
}

int Square::bunnies() const { return bunnies_; }
int Square::male_wolves() const { return male_wolves_; }
int Square::female_wolves() const { return female_wolves_; }
int Square::vector_index() const { return vector_index_; }
void Square::AddBunny() { ++bunnies_; }
void Square::RemoveBunny() { --bunnies_; }
void Square::AddFemaleWolf() { ++female_wolves_; }
void Square::AddMaleWolf() { ++male_wolves_; }

Game::Game(int columns, int rows) {
  columns_ = columns;
  rows_ = rows;
  map_tiles = std::vector<uint8_t>(rows * columns);
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
  CreateBunny(90);
  CreateBunny(71);
  for (auto x : bunnies_vector){
    std::cout << "Bunny id: " << x.bunny_id() << ", ";
    std::cout << "Bunny pos: " << x.grid_position() << '\n';
  }
  CreateWolf(90);
  CreateWolf(90);
  CreateWolf(90);
  CreateWolf(91);
  CreateWolf(91);
  CreateWolf(92);
  CreateWolf(93);
  CreateWolf(94);
  bunnies_vector[0].Move(columns_, rows_, squares_vector, map_tiles);
  for (auto x : bunnies_vector){
    std::cout << "Bunny id: " << x.bunny_id() << ", ";
    std::cout << "Bunny pos: " << x.grid_position() << '\n';
  }
  square_map.Update(map_tiles);
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
void Game::CreateBunny(int pos) {
  bunnies_vector.emplace_back(Bunny(pos, bunnies_vector));
  squares_vector[pos].AddBunny();
  map_tiles[pos] |= 0b00000001u;
}
void Game::CreateWolf(int pos) {
  std::random_device rd;
  std::uniform_int_distribution<int> distribution(0, 1);
  if (distribution(rd)) {
    female_wolves_vector.emplace_back(FemaleWolf(pos, female_wolves_vector));
    squares_vector[pos].AddFemaleWolf();
    map_tiles[pos] |= 0b00000010u;
  } else {
    male_wolves_vector.emplace_back(MaleWolf(pos, male_wolves_vector));
    squares_vector[pos].AddMaleWolf();
    map_tiles[pos] |= 0b00000100u;
  }
}


