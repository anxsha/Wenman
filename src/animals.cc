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

Bunny::Bunny(int pos, std::vector<Bunny>& v) {
  grid_position_ = pos;
  bunny_id_ = v.size();
}
int Bunny::GridPosition() const { return grid_position_; }
int Bunny::BunnyId() const { return bunny_id_; }
void Bunny::Move(int columns, int rows, std::vector<Square>& vs, std::vector<uint8_t>& map_tiles) {
  std::vector<int> possible_moves = FindNeighbouringSquares(columns, rows, grid_position_);
  std::random_device rd{};
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

FemaleWolf::FemaleWolf(int pos, std::vector<FemaleWolf>& v) {
  grid_position_ = pos;
  female_wolf_id_ = v.size();
  fat_ = 1.0;
}
double FemaleWolf::Fat() const { return fat_; }
int FemaleWolf::GridPosition() const { return grid_position_; }
int FemaleWolf::FemaleWolfId() const { return female_wolf_id_; }
void FemaleWolf::Move(int columns,
                      int rows,
                      std::vector<Square>& vs,
                      std::vector<uint8_t>& map_tiles,
                      std::vector<Bunny>& vb,
                      std::vector<FemaleWolf>& vfw) {
  fat_ -= 0.1;
  if (fat_ > 0) {
    std::vector<int> possible_moves = FindNeighbouringSquares(columns, rows, grid_position_);
    int move_square{};
    bool neighb_bunny = false;
    for (auto& move : possible_moves) {
      if (vs.at(move).Bunnies() > 0) {
        move_square = move;
        neighb_bunny = true;
        break;
      }
    }
    if (!neighb_bunny) {
      std::random_device rd{};
      // make a random correct move
      std::uniform_int_distribution<int> moves_distribution(0, possible_moves.size() - 1);
      int rd_number = moves_distribution(rd);
      int random_move = possible_moves.at(rd_number);
      vs.at(grid_position_).RemoveFemaleWolf();
      if (vs.at(grid_position_).FemaleWolves() < 1) {
        map_tiles.at(grid_position_) &= 0b11111101u;
      }
      grid_position_ = random_move;
      vs.at(grid_position_).AddFemaleWolf();
      map_tiles.at(grid_position_) |= 0b00000010u;
    } else { // a neighbouring bunny exists -> gets eaten
      vs.at(grid_position_).RemoveFemaleWolf();
      if (vs.at(grid_position_).FemaleWolves() < 1) {
        map_tiles.at(grid_position_) &= 0b11111101u;
      }
      grid_position_ = move_square;
      vs.at(grid_position_).AddFemaleWolf();
      map_tiles.at(grid_position_) |= 0b00000010u;
      // Eating the bunny
      int i = 0;
      for (auto& bunny : vb) {
        if (bunny.GridPosition() == move_square) {
          vs.at(move_square).RemoveBunny();
          if (vs.at(move_square).Bunnies() < 1) {
            map_tiles.at(move_square) &= 0b11111110u;
          }
          vb.erase(vb.begin() + i);
          fat_ += 1.0;
          break;
        }
        ++i;
      }
    }
  } else {
    int ix = female_wolf_id_;
    vs.at(grid_position_).RemoveFemaleWolf();
    if (vs.at(grid_position_).FemaleWolves() < 1) {
      map_tiles.at(grid_position_) &= 0b11111101u;
    }
    vfw.erase(vfw.begin() + female_wolf_id_);
    for (int i = ix; i < vfw.size(); ++i) {
      vfw.at(i).female_wolf_id_ = i;
    }
  }
}

MaleWolf::MaleWolf(int pos, std::vector<MaleWolf>& v) {
  grid_position_ = pos;
  male_wolf_id_ = v.size();
  fat_ = 1.0;
}
double MaleWolf::Fat() const { return fat_; }
int MaleWolf::GridPosition() const { return grid_position_; }
int MaleWolf::MaleWolfId() const { return male_wolf_id_; }
