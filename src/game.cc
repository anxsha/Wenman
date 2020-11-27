//
// Created by Jakub Molek on 22/10/2020.
//
#include <iostream>
#include <random>
#include <string>

#include "game.h"

Square::Square(std::vector<Square>& v) {
  bunnies_ = 0;
  male_wolves_ = 0;
  female_wolves_ = 0;
  vector_index_ = distance(v.begin(), v.end());
}

int Square::Bunnies() const { return bunnies_; }
int Square::MaleWolves() const { return male_wolves_; }
int Square::FemaleWolves() const { return female_wolves_; }
int Square::VectorIndex() const { return vector_index_; }
void Square::AddBunny() { ++bunnies_; }
void Square::RemoveBunny() { --bunnies_; }
void Square::AddFemaleWolf() { ++female_wolves_; }
void Square::RemoveFemaleWolf() { --female_wolves_; }
void Square::AddMaleWolf() { ++male_wolves_; }
void Square::RemoveMaleWolf() { --male_wolves_; }

Game::Game(int columns, int rows) {
  columns_ = columns;
  rows_ = rows;
  map_tiles = std::vector<uint8_t>(rows * columns);
  for (int i = 0; i < map_tiles.size(); ++i) {
    squares_vector.emplace_back(squares_vector);
  }
  if (!font.loadFromFile("../resources/font.ttf")) {
    std::exit(1);
  }
  if (!square_map.Load("../resources/tileset1.png", sf::Vector2u(60, 60), map_tiles, columns, rows)) {
    std::exit(1);
  }
}
void Game::CreateBunny(int pos) {
  bunnies_vector.emplace_back(pos, bunnies_vector);
  squares_vector[pos].AddBunny();
  map_tiles[pos] |= 0b00000001u;
}
void Game::CreateWolf(int pos) {
  std::random_device rd;
  std::uniform_int_distribution<int> distribution(0, 1);
  if (distribution(rd)) {
    female_wolves_vector.emplace_back(pos, female_wolves_vector);
    squares_vector[pos].AddFemaleWolf();
    map_tiles[pos] |= 0b00000010u;
  } else {
    male_wolves_vector.emplace_back(pos, male_wolves_vector);
    squares_vector[pos].AddMaleWolf();
    map_tiles[pos] |= 0b00000100u;
  }
}
void Game::BunnyTurnActions(sf::RenderWindow& window) {
  sf::Clock clock;
  for (auto& bunny : bunnies_vector) {
    // 20% chance for the bunny to reproduce
    std::random_device rd;
    std::uniform_int_distribution<int> reproduction_distribution(1, 10);
    if (reproduction_distribution(rd) < 3) {
      CreateBunny(bunny.GridPosition());
    }
  }
  for (auto& bunny : bunnies_vector) {
    bunny.Move(columns_, rows_, squares_vector, map_tiles);
  }
  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  window.display();
  while (clock.getElapsedTime().asSeconds() < 3);
  clock.restart();
}
void Game::WolfTurnActions(sf::RenderWindow& window) {
  sf::Clock clock;
  std::vector<int> wolves_birth_squares {};

  for (auto [i, v_size] = std::tuple{0, male_wolves_vector.size()}; i < v_size; ++i) {
    if (male_wolves_vector.at(i).Move(columns_, rows_, squares_vector, map_tiles, bunnies_vector, male_wolves_vector, female_wolves_vector)) {
      --i;
      v_size = male_wolves_vector.size();
    }
  }

  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  window.display();
  while (clock.getElapsedTime().asSeconds() < 3);
  clock.restart();

  for (auto [i, v_size] = std::tuple{0, female_wolves_vector.size()}; i < v_size; ++i) {
    if (female_wolves_vector.at(i).Move(columns_, rows_, squares_vector, map_tiles, bunnies_vector, female_wolves_vector)) {
      --i;
      v_size = female_wolves_vector.size();
    } else {
      if (female_wolves_vector.at(i).HandleGestation()) {
        wolves_birth_squares.push_back(female_wolves_vector.at(i).GridPosition());
      }
    }
  }

  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  window.display();
  while (clock.getElapsedTime().asSeconds() < 1);
  clock.restart();

  for (auto& i : wolves_birth_squares) {
    CreateWolf(i);
  }
  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  window.display();
  while (clock.getElapsedTime().asSeconds() < 3);
  clock.restart();
}
void Game::DrawAnimalsCount(sf::RenderWindow& window) {
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(14);
  text.setFillColor(sf::Color::Black);
  for (auto& square : squares_vector) {
    if (square.Bunnies() > 1) {
      int row = square.VectorIndex() / columns_;
      int col = square.VectorIndex() % columns_;
      text.setPosition(60 * col + 6.f, 60 * row + 5.f);
      text.setString(std::to_string(square.Bunnies()));
      window.draw(text);
    }
    if (square.MaleWolves() > 1) {
      int row = square.VectorIndex() / columns_;
      int col = square.VectorIndex() % columns_;
      text.setPosition(60 * col + 33.f, 60 * row + 45.f);
      text.setString(std::to_string(square.MaleWolves()));
      window.draw(text);
    }
    if (square.FemaleWolves() > 1) {
      int row = square.VectorIndex() / columns_;
      int col = square.VectorIndex() % columns_;
      text.setPosition(60 * col + 47.f, 60 * row + 19.f);
      text.setString(std::to_string(square.FemaleWolves()));
      window.draw(text);
    }
  }
}
void Game::SetInitialState() {
  CreateWolf(30);
  CreateWolf(31);
  CreateWolf(24);
  CreateWolf(24);
  CreateWolf(24);
  CreateWolf(24);
  CreateBunny(0);
  CreateBunny(33);
  CreateBunny(40);
  CreateBunny(0);

}
void Game::Run() {
  sf::RenderWindow window(sf::VideoMode(1402, 840), "Wenman");
  window.setFramerateLimit(3);

  SetInitialState();

  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    BunnyTurnActions(window);
    WolfTurnActions(window);
  }
}