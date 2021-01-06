//
// Created by Jakub Molek on 25/12/2020.
//

#ifndef WENMAN_SRC_MALE_WOLF_H_
#define WENMAN_SRC_MALE_WOLF_H_

#include "wolf.h"
///
/// A male wolf prioritizes making a move that allows it to eat a bunny.
/// If not possible, it looks for a female wolf.
/// When no neighbouring female wolves, chooses a random neighbouring square.
/// If the female wolf is not pregnant, gestation starts and a new wolf
/// is created after 2 female moves.
///
class MaleWolf : public Wolf {
 public:
  ///
  /// Initializes the wolf with fat, a chosen position and its id being the current
  /// size of male wolves' vector (its index therein).
  ///
  MaleWolf(int pos, std::vector<MaleWolf>& v, double initial_fat);
  ///
  /// Decreases fat by 0.1. If fat is not greater than 0 -> wolf dies.
  /// Else, evaluate all possible moves, taking hedge into consideration
  /// if present. Prioritize eating a random neigbouring bunny. Then
  /// moving to a neighbouring female wolf and if its gestation status
  /// =0, start pregnancy. Else, make a random move.
  /// \param game Game
  /// \return 1 if fat reached 0 -> wolf died and is deleted, 0 else
  ///
  int Move(Game& game) override;
};

#endif //WENMAN_SRC_MALE_WOLF_H_
