//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN__ANIMALS_H_
#define WENMAN__ANIMALS_H_

#include <vector>

// Declaration of needed Square class
class Square;

/// Doc this function
std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index);

class MaleWolf {
 public:
  [[nodiscard]] double fat() const;
  [[nodiscard]] int grid_position() const;
  [[nodiscard]] int male_wolf_id() const;
  void Move(int columns, int rows);

  MaleWolf(int pos, std::vector<MaleWolf>& v);

 private:
  double fat_;
  int grid_position_;
  int male_wolf_id_;

};

class FemaleWolf {
 public:
  [[nodiscard]] double fat() const;
  [[nodiscard]] int grid_position() const;
  [[nodiscard]] int female_wolf_id() const;
  void Move(int columns, int rows);

  FemaleWolf(int pos, std::vector<FemaleWolf>& v);

 private:
  double fat_;
  int grid_position_;
  int female_wolf_id_;
};

class Bunny {
 public:
  [[nodiscard]] int grid_position() const;
  [[nodiscard]] int bunny_id() const;
  void Move(int columns, int rows, std::vector<Square>& vs, std::vector<uint8_t>& map_tiles);

  Bunny(int pos, std::vector<Bunny>& v);

 private:
  int grid_position_;
  int bunny_id_;
};

#endif //WENMAN__ANIMALS_H_
