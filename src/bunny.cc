//
// Created by Jakub Molek on 24/12/2020.
//

#include "bunny.h"
#include "square.h"

#include <random>

Bunny::Bunny(int pos, std::vector<Bunny>& v) {
  grid_position_ = pos;
  bunny_id_ = v.size();
}
int Bunny::GridPosition() const { return grid_position_; }
int Bunny::BunnyId() const { return bunny_id_; }
void Bunny::Move(int columns, int rows, std::vector<Square>& vs, std::vector<uint8_t>& map_tiles) {
  std::vector<int> possible_moves = FindNeighbouringSquares(columns, rows, grid_position_);
  std::random_device rd {};
  // make a random correct move
  std::uniform_int_distribution<int> moves_distribution(0, possible_moves.size() - 1);
  int rd_number = moves_distribution(rd);
  int random_move = possible_moves.at(rd_number);
  vs.at(grid_position_).RemoveBunny();
  if (vs.at(grid_position_).Bunnies() < 1) {
    map_tiles.at(grid_position_) &= 0b11111110u;
  }
  grid_position_ = random_move;
  vs.at(grid_position_).AddBunny();
  map_tiles.at(grid_position_) |= 0b00000001u;
}