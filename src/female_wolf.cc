//
// Created by Jakub Molek on 24/12/2020.
//

#include "female_wolf.h"
#include "game.h"

FemaleWolf::FemaleWolf(int pos, std::vector<FemaleWolf>& v, double initial_fat) : Wolf {pos, static_cast<int>(v.size()),
                                                                                        initial_fat}, gestation_ {0} {}
int FemaleWolf::Gestation() const { return gestation_; }
int FemaleWolf::HandleGestation(bool set_pregnancy) {
  if (set_pregnancy && !gestation_) {
    gestation_ = 2;
  } else {
    if (gestation_ == 2) {
      --gestation_;
    } else if (gestation_ == 1) {
      gestation_ = 0;
      return 1;
    }
  }
  return 0;
}

int FemaleWolf::Move(Game& game) {
  fat_ -= 0.1;
  if (fat_ > 0) {
    std::vector<int> possible_moves = FindNeighbouringSquares(game.columns_, game.rows_, grid_position_);
    // if hedge present, remove bunny-only squares from possible moves
    if (game.with_hedge_) {
      for (auto& index : game.hedge_area_squares) {
        possible_moves.erase(std::remove(possible_moves.begin(), possible_moves.end(), index), possible_moves.end());
      }
    }
    std::vector<int> neighb_bunny_squares {};
    bool neighb_bunny = false;
    // find properly-neighbouring squares with bunnies
    for (auto& move : possible_moves) {
      if (game.squares_vector.at(move).Bunnies() > 0) {
        neighb_bunny_squares.push_back(move);
        neighb_bunny = true;
      }
    }
    if (!neighb_bunny) {
      MakeRandomMove(game, WolfSex::kFemale, possible_moves);
    } else {
      EatNeighbBunny(game, WolfSex::kFemale, neighb_bunny_squares);
    }
  } else {
    DeleteWolf(game, WolfSex::kFemale);
    return 1;
  }
  return 0;
}