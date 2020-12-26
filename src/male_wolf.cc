//
// Created by Jakub Molek on 25/12/2020.
//

#include "male_wolf.h"

#include <random>

#include "game.h"

MaleWolf::MaleWolf(int pos, std::vector<MaleWolf>& v, double initial_fat) : Wolf {pos, static_cast<int>(v.size()),
                                                                                  initial_fat} {}
int MaleWolf::Move(Game& game) {
  fat_ -= 0.1;
  if (fat_ > 0) {
    std::vector<int> possible_moves = FindNeighbouringSquares(game.columns_, game.rows_, grid_position_);
    if (game.with_hedge_) {
      for (auto& index : game.hedge_area_squares) {
        possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), index), possible_moves.end());
      }
    }
    bool neighb_bunny = false;
    bool neighb_female_wolf = false;
    std::vector<int> neighb_female_wolf_squares {};
    std::vector<int> neighb_bunny_squares {};
    for (auto& move : possible_moves) {
      if (game.squares_vector.at(move).Bunnies() > 0) {
        neighb_bunny_squares.push_back(move);
        neighb_bunny = true;
      }
      if (game.squares_vector.at(move).FemaleWolves() > 0) {
        neighb_female_wolf_squares.push_back(move);
        neighb_female_wolf = true;
      }
    }
    if (neighb_bunny) {
      EatNeighbBunny(game, WolfSex::kMale, neighb_bunny_squares);
    } else if (neighb_female_wolf) {
      std::random_device rd {};
      std::uniform_int_distribution<int> moves_distribution(0, neighb_female_wolf_squares.size() - 1);
      int rd_number = moves_distribution(rd);
      int move_square = neighb_female_wolf_squares.at(rd_number);
      game.squares_vector.at(grid_position_).RemoveMaleWolf();
      if (game.squares_vector.at(grid_position_).MaleWolves() < 1) {
        game.map_tiles.at(grid_position_) &= 0b11111011u;
      }
      grid_position_ = move_square;
      game.squares_vector.at(grid_position_).AddMaleWolf();
      game.map_tiles.at(grid_position_) |= 0b00000100u;

      for (auto& fw : game.female_wolves_vector) {
        if (fw.GridPosition() == move_square && !fw.Gestation()) {
          fw.HandleGestation(true);
          break;
        }
      }

    } else {
      MakeRandomMove(game, WolfSex::kMale, possible_moves);
    }
  } else {
    DeleteWolf(game, WolfSex::kMale);
    return 1;
  }
  return 0;
}