//
// Created by Jakub Molek on 25/12/2020.
//

#ifndef WENMAN_SRC_MALE_WOLF_H_
#define WENMAN_SRC_MALE_WOLF_H_

#include "wolf.h"

class MaleWolf : public Wolf {
 public:
  MaleWolf(int pos, std::vector<MaleWolf>& v, double initial_fat);
  int Move(Game& game);
};

#endif //WENMAN_SRC_MALE_WOLF_H_
