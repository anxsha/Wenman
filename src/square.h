//
// Created by Jakub Molek on 25/12/2020.
//

#ifndef WENMAN_SRC_SQUARE_H_
#define WENMAN_SRC_SQUARE_H_

#include <vector>

std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index);

///
/// Every object of this class contains information about one assigned
/// graphical square. It is the source, based on which graphical grid is
/// generated.
///
class Square {
 public:
  /// Returns the number of bunnies that occupy this square.
  [[nodiscard]] int Bunnies() const;
  /// Returns the number of male wolves that occupy this square.
  [[nodiscard]] int MaleWolves() const;
  /// Returns the number of female wolves that occupy this square.
  [[nodiscard]] int FemaleWolves() const;
  /// Returns the index of this square in Game's square vector that contains them all.
  [[nodiscard]] int VectorIndex() const;
  /// Increments the number of bunnies on this square.
  void AddBunny();
  /// Decrements the number of bunnies on this square.
  void RemoveBunny();
  /// Increments the number of female wolves on this square.
  void AddFemaleWolf();
  /// Decrements the number of female wolves on this square.
  void RemoveFemaleWolf();
  /// Increments the number of male wolves on this square.
  void AddMaleWolf();
  /// Decrements the number of male wolves on this square.
  void RemoveMaleWolf();
  ///
  /// The constructor sets the number of all animals on this square to 0.
  /// Receives the Game's vector which consists of all squares as a parameter to identify
  /// its index therein.
  ///
  explicit Square(std::vector<Square>& v);

 private:
  int bunnies_;   ///< Number of Bunnies present on that square
  int male_wolves_;   ///< Number of male wolves present on that square
  int female_wolves_;   ///< Number of female wolves present on that square
  int vector_index_;    ///< Number identifying that square's index in the game's grid vector

};

#endif //WENMAN_SRC_SQUARE_H_
