//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_BUNNY_H_
#define WENMAN_SRC_BUNNY_H_

#include <vector>

// forward declarations
class Square;
class Game;
///
/// The simplest animal, its lifetime does not depend on any resources.
/// Its move is always random. Can be eaten by a neighbouring wolf.
/// At every turn, there is a 20% chance a bunny reproduces.
/// If a hedge-confined area is present, only bunnies can move inside.
///
class Bunny {
 public:
  /// Getter for the bunny's position (index of the square)
  int GridPosition() const;
  ///
  /// Calculates correct moves (neighbouring squares) and chooses one randomly.
  /// Afterwards, updates game's properties based on the move.
  ///
  void Move(Game& game);
  ///
  /// Initializes the bunny with a chosen position and its id being the current
  /// size of bunnies' vector (its index therein)
  ///
  Bunny(int pos, std::vector<Bunny>& v);

 private:
  int grid_position_;
  int bunny_id_;
};

#endif //WENMAN_SRC_BUNNY_H_
