//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_BUNNY_H_
#define WENMAN_SRC_BUNNY_H_

#include <vector>

class Square;

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

#endif //WENMAN_SRC_BUNNY_H_
