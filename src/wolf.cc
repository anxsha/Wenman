//
// Created by Jakub Molek on 24/12/2020.
//

#include "wolf.h"
#include "game.h"
#include <random>

Wolf::Wolf(int pos, int v_size, double initial_fat) : grid_position_ {pos},
                                                      id_ {v_size}, fat_ {initial_fat} {}
double Wolf::Fat() const { return fat_; }
int Wolf::GridPosition() const { return grid_position_; }
int Wolf::Id() const { return id_; }
void Wolf::EatNeighbBunny(Game& game, const WolfSex& sex, const std::vector<int>& neighb_bunny_squares) {
  // choosing a random bunny from the possible options
  std::random_device rd {};
  std::uniform_int_distribution<int> moves_distribution(0, neighb_bunny_squares.size() - 1);
  int rd_number = moves_distribution(rd);
  int move_square = neighb_bunny_squares.at(rd_number);
  // handling squares' wolf counter and bits of that square in game's map tiles
  /*-------------------------------------------------------
   * To grasp the usage of bitwise operations, head over to
   * GraphicalGrid's Load function, squares_states param.
  -------------------------------------------------------*/
  if (sex == WolfSex::kFemale) {
    game.squares_vector.at(grid_position_).RemoveFemaleWolf();
    if (game.squares_vector.at(grid_position_).FemaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111101u;
    }
    grid_position_ = move_square;
    game.squares_vector.at(grid_position_).AddFemaleWolf();
    game.map_tiles.at(grid_position_) |= 0b00000010u;
  } else {
    game.squares_vector.at(grid_position_).RemoveMaleWolf();
    if (game.squares_vector.at(grid_position_).MaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111011u;
    }
    grid_position_ = move_square;
    game.squares_vector.at(grid_position_).AddMaleWolf();
    game.map_tiles.at(grid_position_) |= 0b00000100u;
  }
  // find the bunny on selected square in its game vector
  int i = 0;
  for (auto& bunny : game.bunnies_vector) {
    if (bunny.GridPosition() == move_square) {
      game.squares_vector.at(move_square).RemoveBunny();
      if (game.squares_vector.at(move_square).Bunnies() < 1) {
        game.map_tiles.at(move_square) &= 0b11111110u;
      }
      game.bunnies_vector.erase(game.bunnies_vector.begin() + i);
      // limit wolf's fat to 2.0
      fat_ <= 1 ? fat_ += 1.0 : fat_ = 2.0;
      break;
    }
    ++i;
  }
}
void Wolf::DeleteWolf(Game& game, const WolfSex& sex) {
  int ix = id_;
  /*-------------------------------------------------------
   * To grasp the usage of bitwise operations, head over to
   * GraphicalGrid's Load function, squares_states param.
  -------------------------------------------------------*/
  if (sex == WolfSex::kFemale) {
    game.squares_vector.at(grid_position_).RemoveFemaleWolf();
    if (game.squares_vector.at(grid_position_).FemaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111101u;
    }
    game.female_wolves_vector.erase(game.female_wolves_vector.begin() + id_);
    for (int i = ix; i < game.female_wolves_vector.size(); ++i) {
      game.female_wolves_vector.at(i).id_ = i;
    }
  } else {
    game.squares_vector.at(grid_position_).RemoveMaleWolf();
    if (game.squares_vector.at(grid_position_).MaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111011u;
    }
    game.male_wolves_vector.erase(game.male_wolves_vector.begin() + id_);
    for (int i = ix; i < game.male_wolves_vector.size(); ++i) {
      game.male_wolves_vector.at(i).id_ = i;
    }
  }
}
void Wolf::MakeRandomMove(Game& game, const WolfSex& sex, const std::vector<int>& possible_moves) {
  std::random_device rd {};
  std::uniform_int_distribution<int> moves_distribution(0, possible_moves.size() - 1);
  int rd_number = moves_distribution(rd);
  int random_move = possible_moves.at(rd_number);
  /*-------------------------------------------------------
   * To grasp the usage of bitwise operations, head over to
   * GraphicalGrid's Load function, squares_states param.
  -------------------------------------------------------*/
  if (sex == WolfSex::kFemale) {
    game.squares_vector.at(grid_position_).RemoveFemaleWolf();
    if (game.squares_vector.at(grid_position_).FemaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111101u;
    }
    grid_position_ = random_move;
    game.squares_vector.at(grid_position_).AddFemaleWolf();
    game.map_tiles.at(grid_position_) |= 0b00000010u;
  } else {
    game.squares_vector.at(grid_position_).RemoveMaleWolf();
    if (game.squares_vector.at(grid_position_).MaleWolves() < 1) {
      game.map_tiles.at(grid_position_) &= 0b11111011u;
    }
    grid_position_ = random_move;
    game.squares_vector.at(grid_position_).AddMaleWolf();
    game.map_tiles.at(grid_position_) |= 0b00000100u;
  }
}