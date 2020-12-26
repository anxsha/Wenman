//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_WOLF_H_
#define WENMAN_SRC_WOLF_H_

#include <vector>

class Game;

enum class WolfSex {
  kMale,
  kFemale
};

class Wolf {
 public:
  Wolf (int pos, int v_size, double initial_fat);
  [[nodiscard]] double Fat() const;
  [[nodiscard]] int GridPosition() const;
  [[nodiscard]] int Id() const;
  void EatNeighbBunny(Game& game, const WolfSex& sex, const std::vector<int>& neighb_bunny_squares);
  void DeleteWolf(Game& game, const WolfSex& sex);
  void MakeRandomMove(Game& game, const WolfSex& sex, const std::vector<int>& possible_moves);
 protected:
  double fat_;
  int grid_position_;
  int id_;
};

#endif //WENMAN_SRC_WOLF_H_
