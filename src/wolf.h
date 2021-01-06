//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_WOLF_H_
#define WENMAN_SRC_WOLF_H_

#include <vector>

// forward declaration
class Game;

enum class WolfSex {
  kMale,
  kFemale
};
///
/// Consists of some members and functions that can be shared
/// between female and male wolves.
///
class Wolf {
 public:
  ///
  /// Initializes the wolf with fat, a chosen position and its id being the current
  /// size of that sex's wolves' vector (its index therein).
  ///
  Wolf (int pos, int v_size, double initial_fat);
  /// Fat level getter
  double Fat() const;
  /// Grid position getter
  int GridPosition() const;
  /// Wolf's id getter
  int Id() const;
  ///
  /// Chooses one random bunny from the possible options
  /// and handles the move by properly managing
  /// squares' properties depending on which
  /// (female/male) wolf called the function.
  ///
  void EatNeighbBunny(Game& game, const WolfSex& sex, const std::vector<int>& neighb_bunny_squares);
  ///
  /// Handles that wolf's square's properties.
  /// Erases the wolf from correct game's wolves vector
  /// depending on which (female/male) wolf dies.
  ///
  void DeleteWolf(Game& game, const WolfSex& sex);
  ///
  /// Choooses a random square from the possible options and makes a move.
  /// Handles squares' properties.
  ///
  void MakeRandomMove(Game& game, const WolfSex& sex, const std::vector<int>& possible_moves);
  virtual int Move(Game& game) = 0;
 protected:
  ///
  /// Fat level of a wolf. Default initial value is 1.0. Every move
  /// decreases it by 0.1. Eating a bunny grants 1.0 up to a maximum of 2.0.
  ///
  double fat_;
  /// Position of a wolf on the grid. Index of that square.
  int grid_position_;
  /// Id of a wolf - its index in the appropriate game's vector.
  int id_;
};

#endif //WENMAN_SRC_WOLF_H_
