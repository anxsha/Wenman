//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN_SRC_ANIMALS_H_
#define WENMAN_SRC_ANIMALS_H_

#include <vector>

// Declaration of needed Square class
class Square;
class Game;

/// Doc this function
std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index);

class MaleWolf {
 public:
  [[nodiscard]] double Fat() const;
  [[nodiscard]] int GridPosition() const;
  [[nodiscard]] int MaleWolfId() const;
  void Move(int columns, int rows);

  MaleWolf(int pos, std::vector<MaleWolf>& v);

 private:
  double fat_;
  int grid_position_;
  int male_wolf_id_;

};

class FemaleWolf {
 public:
  [[nodiscard]] double Fat() const;
  [[nodiscard]] int GridPosition() const;
  [[nodiscard]] int FemaleWolfId() const;
  void Move(int columns, int rows);

  FemaleWolf(int pos, std::vector<FemaleWolf>& v);

 private:
  double fat_;
  int grid_position_;
  int female_wolf_id_;
};

class Bunny {
 public:
  [[nodiscard]] int GridPosition() const;
  [[nodiscard]] int BunnyId() const;
  void Move(int columns, int rows, std::vector<Square>& vs, std::vector<uint8_t>& map_tiles);

  Bunny(int pos, std::vector<Bunny>& v);

 private:
  int grid_position_;
  int bunny_id_;
};

#endif //WENMAN_SRC_ANIMALS_H_
