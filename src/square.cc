//
// Created by Jakub Molek on 25/12/2020.
//

#include "square.h"

std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index) {
  std::vector<int> v {};
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
  if (row < (size_y - 1) && col < (size_x - 1)) {
    int lower_right = (row + 1) * size_x + (col + 1);
    v.push_back(lower_right);
  }
  return v;
}

Square::Square(const std::vector<Square>& v) : bunnies_ {0},
                                               male_wolves_ {0},
                                               female_wolves_ {0},
                                               vector_index_ {static_cast<int>(distance(v.begin(), v.end()))} {}
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