//
// Created by Jakub Molek on 22/10/2020.
//

#include "animals.h"

Bunny::Bunny(int pos, std::vector<Bunny>& v) {
  grid_position_ = pos;
  bunny_id_ = v.size();
}

