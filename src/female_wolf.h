//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_FEMALE_WOLF_H_
#define WENMAN_SRC_FEMALE_WOLF_H_

#include "wolf.h"
///
/// A female wolf prioritizes making a move that allows it to eat a bunny.
/// If not possible, chooses a random neighbouring square.
/// When a male wolf moves to a square with a female one (and w/o a bunny),
/// the female gets pregnant (unless already had been) for the next 2 turns.
/// Then gives birth to a wolf of random sex, passing them its fat value.
///
class FemaleWolf : public Wolf {
 public:
  ///
  /// Initializes the wolf with a chosen position and its id being the current
  /// size of female wolves' vector (its index therein).
  /// Initializes fat and sets gestation status to 0.
  ///
  FemaleWolf(int pos, std::vector<FemaleWolf>& v, double initial_fat);
  /// Gestation status getter
  [[nodiscard]] int Gestation() const;
  ///
  /// Changes the current gestation status based on its value
  /// (when =2, decrement, =1 -> decrement and return 1 signalling completion).
  /// If set_pregnancy is true and gestation_ equals 0,
  /// start pregnancy (set status to 2).
  /// \param set_pregnancy set to true when called by a male wolf's move
  /// \return an integer val of 1 - when giving birth (i.e. create a wolf)
  ///         or 0 else
  ///
  int HandleGestation(bool set_pregnancy = false);
  ///
  /// Decreases fat by 0.1. If fat is not greater than 0 -> wolf dies.
  /// Else, evaluate all possible moves, taking hedge into consideration
  /// if present. Prioritize eating a random neigbouring bunny, else make a
  /// random move.
  /// \param game Game
  /// \return 1 if fat reached 0 -> wolf died and is deleted, 0 else
  ///
  int Move(Game& game) override;
 private:
  /// =2 means gestation started this turn, 1 -> prev. turn, 0 -> no pregnancy
  int gestation_;
};

#endif //WENMAN_SRC_FEMALE_WOLF_H_
