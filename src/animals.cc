//
// Created by Jakub Molek on 22/10/2020.
//
#include <random>
#include <iostream>

#include "game.h"
#include "animals.h"

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

Bunny::Bunny(int pos, std::vector<Bunny> &v) {
  grid_position_ = pos;
  bunny_id_ = v.size();
}
int Bunny::grid_position() const { return grid_position_; }
int Bunny::bunny_id() const { return bunny_id_; }
void Bunny::Move(int columns, int rows, std::vector<Square>& vs, std::vector<uint8_t>& map_tiles) {
  //TODO create bunny 20%
  std::vector<int> possible_moves = FindNeighbouringSquares(columns, rows, grid_position_);
  std::random_device rd;
  std::uniform_int_distribution<int> distribution(0, possible_moves.size() - 1);
  int rd_number = distribution(rd);
  int random_move = possible_moves[rd_number];
  vs[grid_position_].RemoveBunny();
  if (vs[grid_position_].bunnies() < 1) {
    map_tiles[grid_position_] &= 0b11111110;
  }
  grid_position_ = random_move;
  vs[grid_position_].AddBunny();
  map_tiles[grid_position_] |= 0b00000001;
}

FemaleWolf::FemaleWolf(int pos, std::vector<FemaleWolf> &v) {
  grid_position_ = pos;
  female_wolf_id_ = v.size();
  fat_ = 1.0;
}
double FemaleWolf::fat() const { return fat_; }
int FemaleWolf::grid_position() const { return grid_position_; }
int FemaleWolf::female_wolf_id() const { return female_wolf_id_; }

MaleWolf::MaleWolf(int pos, std::vector<MaleWolf> &v) {
  grid_position_ = pos;
  male_wolf_id_ = v.size();
  fat_ = 1.0;
}
double MaleWolf::fat() const { return fat_; }
int MaleWolf::grid_position() const { return grid_position_; }
int MaleWolf::male_wolf_id() const { return male_wolf_id_; }
