//
// Created by Jakub Molek on 24/12/2020.
//

#include "bunny.h"
#include "square.h"
#include "game.h"
#include <random>

Bunny::Bunny(int pos, std::vector<Bunny>& v) : grid_position_ {pos}, bunny_id_ {static_cast<int>(v.size())} {}
int Bunny::GridPosition() const { return grid_position_; }
void Bunny::Move(Game& game) {

  /*-------------------------------------------------------
   * To grasp the usage of bitwise operations, head over to
   * GraphicalGrid's Load function, squares_states param.
  -------------------------------------------------------*/

  std::vector<int> possible_moves = FindNeighbouringSquares(game.columns_, game.rows_, grid_position_);
  std::random_device rd {};
  // make a random correct move
  std::uniform_int_distribution<int> moves_distribution(0, possible_moves.size() - 1);
  int rd_number = moves_distribution(rd);
  int random_move = possible_moves.at(rd_number);
  // decrement the square's counter of bunnies
  game.squares_vector.at(grid_position_).RemoveBunny();
  // if no bunnies present on that square, use a bit mask
  // to remove bunny's icon - represented by the LSB
  if (game.squares_vector.at(grid_position_).Bunnies() < 1) {
    game.map_tiles.at(grid_position_) &= 0b11111110u;
  }
  // set the new position
  grid_position_ = random_move;
  // increment the counter of bunnies
  game.squares_vector.at(grid_position_).AddBunny();
  // assure the square displays a bunny with OR operator for the bunny bit
  game.map_tiles.at(grid_position_) |= 0b00000001u;
}