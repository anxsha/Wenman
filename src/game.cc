//
// Created by Jakub Molek on 22/10/2020.
//
#include "game.h"
#include <random>
#include <string>

Game::Game(int columns,
           int rows,
           bool set_hedge,
           int hedge_size,
           int hedge_x_origin,
           int hedge_y_origin) : columns_{columns}, rows_{rows}, with_hedge_{set_hedge} {
  // Each graph. square needs info about the tile to be loaded dep. on animals
  map_tiles = std::vector<uint8_t>(rows * columns);
  // Initialize the vector of squares
  for (int i = 0; i < map_tiles.size(); ++i) {
    squares_vector.emplace_back(squares_vector);
  }
  if (with_hedge_) {
    if (!hedge_horizontal.loadFromFile("../resources/hedgeH.png")) {
      std::exit(1);
    }
    if (!hedge_vertical.loadFromFile("../resources/hedgeV.png")) {
      std::exit(1);
    }
    // Prepare vectors of sprites to be drawn onto the window
    hedge_h_texture.loadFromImage(hedge_horizontal);
    hedge_top_sprites = std::vector<sf::Sprite>(hedge_size, sf::Sprite(hedge_h_texture));
    hedge_bottom_sprites = std::vector<sf::Sprite>(hedge_size, sf::Sprite(hedge_h_texture));
    hedge_v_texture.loadFromImage(hedge_vertical);
    hedge_left_sprites = std::vector<sf::Sprite>(hedge_size, sf::Sprite(hedge_v_texture));
    hedge_right_sprites = std::vector<sf::Sprite>(hedge_size, sf::Sprite(hedge_v_texture));
    // Set the position (+ offset) accordingly for each sprite
    for (int i = 0; i < hedge_size; ++i) {
      hedge_top_sprites[i].setPosition((hedge_x_origin - 1) * 60 - 2 + 60 * i, (hedge_y_origin - 1) * 60 - 8);
    }
    for (int i = 0; i < hedge_size; ++i) {
      hedge_bottom_sprites[i].setPosition((hedge_x_origin - 1) * 60 - 2 + 60 * i,
                                          (hedge_y_origin - 1 + hedge_size) * 60 - 8);
    }
    for (int i = 0; i < hedge_size; ++i) {
      hedge_left_sprites[i].setPosition((hedge_x_origin - 1) * 60 - 8, (hedge_y_origin - 1) * 60 - 3 + 60 * i);
    }
    for (int i = 0; i < hedge_size; ++i) {
      hedge_right_sprites[i].setPosition((hedge_x_origin - 1 + hedge_size) * 60 - 8,
                                         (hedge_y_origin - 1) * 60 - 3 + 60 * i);
    }
    hedge_area_squares.reserve(hedge_size * hedge_size);
    for (int i = hedge_y_origin - 1; i < hedge_y_origin - 1 + hedge_size; ++i) {
      for (int j = hedge_x_origin - 1; j < hedge_x_origin - 1 + hedge_size; ++j) {
        hedge_area_squares.push_back(columns * i + j);
      }
    }
  }
  if (!font.loadFromFile("../resources/font.ttf")) {
    std::exit(1);
  }
  if (!square_map.Load("../resources/tileset1.png", sf::Vector2u(60, 60), map_tiles, columns, rows)) {
    std::exit(1);
  }
}
/*-------------------------------------------------------
 * To grasp the usage of bitwise operations, head over to
 * GraphicalGrid's Load function, squares_states param.
-------------------------------------------------------*/
void Game::CreateBunny(int pos) {
  bunnies_vector.emplace_back(pos, bunnies_vector);
  squares_vector.at(pos).AddBunny();
  map_tiles.at(pos) |= 0b00000001u;
}
void Game::CreateWolf(int pos, double fat) {
  std::random_device rd;
  std::uniform_int_distribution<int> distribution(0, 1);
  // Random sex
  if (distribution(rd)) {
    female_wolves_vector.emplace_back(pos, female_wolves_vector, fat);
    squares_vector.at(pos).AddFemaleWolf();
    map_tiles.at(pos) |= 0b00000010u;
  } else {
    male_wolves_vector.emplace_back(pos, male_wolves_vector, fat);
    squares_vector.at(pos).AddMaleWolf();
    map_tiles.at(pos) |= 0b00000100u;
  }
}
void Game::CreateFemaleWolf(int pos, double fat) {
  female_wolves_vector.emplace_back(pos, female_wolves_vector, fat);
  squares_vector.at(pos).AddFemaleWolf();
  map_tiles.at(pos) |= 0b00000010u;
}
void Game::CreateMaleWolf(int pos, double fat) {
  male_wolves_vector.emplace_back(pos, male_wolves_vector, fat);
  squares_vector.at(pos).AddMaleWolf();
  map_tiles.at(pos) |= 0b00000100u;
}
void Game::BunnyTurnActions(sf::RenderWindow& window) {
  std::vector<int> bunnies_birth_data{};
  for (auto& bunny : bunnies_vector) {
    // 20% chance for the bunny to reproduce
    std::random_device rd;
    std::uniform_int_distribution<int> reproduction_distribution(1, 10);
    if (reproduction_distribution(rd) < 3) {
      bunnies_birth_data.push_back(bunny.GridPosition());
    }
  }
  for (auto& el : bunnies_birth_data) {
    CreateBunny(el);
  }
  for (auto& bunny : bunnies_vector) {
    bunny.Move(*this);
  }
  // Update the graphical window
  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  if (with_hedge_) { DrawHedge(window); }
  window.display();
  Freeze(window, 2);
}
void Game::WolfTurnActions(sf::RenderWindow& window) {
  std::vector<std::tuple<int, double>> wolves_birth_data{};

  for (auto[i, v_size] = std::tuple{0, male_wolves_vector.size()}; i < v_size; ++i) {
    if (male_wolves_vector.at(i).Move(*this)) {
      --i;
      v_size = male_wolves_vector.size();
    }
  }
  // Update the graphical window
  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  if (with_hedge_) { DrawHedge(window); }
  window.display();
  Freeze(window, 2);

  // Making a move for every female wolf. If alive, handle gestation.
  // When HandleGestation returns a 1, append to a vector of tuples
  // the (position, fat) of the mother
  for (auto[i, v_size] = std::tuple{0, female_wolves_vector.size()}; i < v_size; ++i) {
    if (female_wolves_vector.at(i).Move(*this)) {
      --i;
      v_size = female_wolves_vector.size();
    } else {
      if (female_wolves_vector.at(i).HandleGestation()) {
        wolves_birth_data.emplace_back(female_wolves_vector.at(i).GridPosition(), female_wolves_vector.at(i).Fat());
      }
    }
  }

  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  if (with_hedge_) { DrawHedge(window); }
  window.display();
  Freeze(window, 1);

  // Create a new wolf for every tuple inserted while handling gestation
  for (auto& el : wolves_birth_data) {
    CreateWolf(std::get<0>(el), std::get<1>(el));
  }
  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  if (with_hedge_) { DrawHedge(window); }
  window.display();
  Freeze(window, 2);
}
void Game::DrawAnimalsCount(sf::RenderWindow& window) {
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(14);
  text.setFillColor(sf::Color::Black);
  // check each animal type in every square
  for (auto& square : squares_vector) {
    // if its count therein is greater than 1, draw a number next to the icon
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
void Game::DrawHedge(sf::RenderWindow& window) {
  for (auto& sprite : hedge_bottom_sprites) { window.draw(sprite); }
  for (auto& sprite : hedge_left_sprites) { window.draw(sprite); }
  for (auto& sprite : hedge_top_sprites) { window.draw(sprite); }
  for (auto& sprite : hedge_right_sprites) { window.draw(sprite); }
}
void Game::Freeze(sf::RenderWindow& window, int n) {
  sf::Clock clock{};
  sf::Event event{};
  while (clock.getElapsedTime().asSeconds() < n) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { window.close(); }
    }
  }
}
void Game::SetInitialState(const std::vector<int>& bunny_squares,
                           const std::vector<int>& female_wolf_squares,
                           const std::vector<int>& male_wolf_squares,
                           sf::RenderWindow& window) {
  for (auto& square : bunny_squares) {
    CreateBunny(square);
  }
  for (auto& square : female_wolf_squares) {
    CreateFemaleWolf(square);
  }
  for (auto& square : male_wolf_squares) {
    CreateMaleWolf(square);
  }

  square_map.Update(map_tiles);
  window.clear();
  window.draw(square_map);
  DrawAnimalsCount(window);
  if (with_hedge_) { DrawHedge(window); }
  window.display();
  Freeze(window, 3);
}
void Game::Run(const std::vector<int>& bunny_squares,
               const std::vector<int>& female_wolf_squares,
               const std::vector<int>& male_wolf_squares) {
  sf::RenderWindow window(sf::VideoMode(columns_ * 60, rows_ * 60 + 2), "Wenman");
  window.setFramerateLimit(3);

  SetInitialState(bunny_squares, female_wolf_squares, male_wolf_squares, window);
  while (window.isOpen()) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) { window.close(); }
    }
    BunnyTurnActions(window);
    WolfTurnActions(window);
  }
}