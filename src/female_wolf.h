//
// Created by Jakub Molek on 24/12/2020.
//

#ifndef WENMAN_SRC_FEMALE_WOLF_H_
#define WENMAN_SRC_FEMALE_WOLF_H_

#include "wolf.h"

class FemaleWolf : public Wolf {
 public:
  FemaleWolf(int pos, std::vector<FemaleWolf>& v, double initial_fat);
  [[nodiscard]] int Gestation() const;
  int HandleGestation(bool set_pregnancy = false);
  int Move(Game& game);
 private:
  int gestation_;
};

#endif //WENMAN_SRC_FEMALE_WOLF_H_
