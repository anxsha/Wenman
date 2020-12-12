//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN_SRC_ANIMALS_H_
#define WENMAN_SRC_ANIMALS_H_

#include <vector>

class Square;
class Game;
class Bunny;
class FemaleWolf;

/// Doc this function
std::vector<int> FindNeighbouringSquares(int size_x, int size_y, int index);

class MaleWolf {
 public:
  [[nodiscard]] double Fat() const;
  [[nodiscard]] int GridPosition() const;
  [[nodiscard]] int MaleWolfId() const;
  int Move(int columns, int rows, std::vector<Square>& vs,
            std::vector<uint8_t>& map_tiles, std::vector<Bunny>& vb,
            std::vector<MaleWolf>& vmw, std::vector<FemaleWolf>& vfw,
            bool with_hedge, std::vector<int>& hedge_area_squares);

  MaleWolf(int pos, std::vector<MaleWolf>& v, double initial_fat = 1.0);

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
  [[nodiscard]] int Gestation() const;
  int HandleGestation(bool set_pregnancy = false);
  int Move(int columns, int rows, std::vector<Square>& vs,
            std::vector<uint8_t>& map_tiles, std::vector<Bunny>& vb,
            std::vector<FemaleWolf>& vfw, bool with_hedge,
            std::vector<int>& hedge_area_squares);

  FemaleWolf(int pos, std::vector<FemaleWolf>& v, double initial_fat = 1.0);

 private:
  double fat_;
  int grid_position_;
  int female_wolf_id_;
  int gestation_;
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
