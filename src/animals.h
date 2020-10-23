//
// Created by Jakub Molek on 22/10/2020.
//

#ifndef WENMAN__ANIMALS_H_
#define WENMAN__ANIMALS_H_

#include <vector>

class MaleWolf {
 public:
  double fat() const;
  int grid_position() const;
  int male_wolf_id() const;
  void Move();

 private:
  double fat_;
  int grid_position_;
  int male_wolf_id_;

};

class FemaleWolf {
 public:
  double fat() const;
  int grid_position() const;
  int female_wolf_id() const;
  void Move();

 private:
  double fat_;
  int grid_position_;
  int female_wolf_id_;
};

class Bunny {
 public:
  int grid_position() const;
  int bunny_id() const;
  void Move();

  Bunny(int pos, std::vector<Bunny>& v);

 private:
  int grid_position_;
  int bunny_id_;
};

#endif //WENMAN__ANIMALS_H_
