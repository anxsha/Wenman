//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN__GAME_H_
#define WENMAN__GAME_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "graphical_grid.h"
#include "animals.h"

/// Doc this function
std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index);

/// Docs of square class
class Square {
 public:
  int bunnies() const;
  int male_wolves() const;
  int female_wolves() const;
  int vector_index() const;

  explicit Square(std::vector<Square>& v); ///< Receives

 private:
  int bunnies_;   ///< Number of bunnies present on that square
  int male_wolves_;   ///< Number of male wolves present on that square
  int female_wolves_;   ///< Number of female wolves present on that square
  int vector_index_;    ///< Number identifying that square's index in the game's grid vector

};

class Game {
 public:
  std::vector<int> map_tiles;
  sf::Font font;
  GraphicalGrid square_map;

  std::vector<Bunny> bunnies_vector {};
  std::vector<MaleWolf> male_wolves_vector {};
  std::vector<FemaleWolf> female_wolves_vector {};
  std::vector<Square> squares_vector {};

  Game(int columns, int rows);
  void Run();
};

#endif //WENMAN__GAME_H_
