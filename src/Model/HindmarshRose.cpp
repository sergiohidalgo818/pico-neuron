/**
 * @file HindmarshRose.cpp
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in c++ for the class of HindmarshRose class
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Model/HindmarshRose.hpp"

HindmarshRose::HindmarshRose(bool synaptic, float initial_time,
                             float time_increment, float x, float y, float z,
                             float e, float S, float m)
    : Model(synaptic, initial_time, time_increment) {
  this->x = x;
  this->y = (time_increment * (1 - 5 * x * x)) / (time_increment - 1);
  this->z = (time_increment * m * S * (x + 1.6)) / (time_increment * m - 1);
  this->e = e;
  this->S = S;
  this->m = m;
}

HindmarshRose::HindmarshRose(bool synaptic, float threshold, float initial_time,
                             float time_increment, float x, float y, float z,
                             float e, float S, float m)
    : Model(synaptic, threshold, initial_time, time_increment) {
  this->x = x;
  this->y = (time_increment * (1 - 5 * x * x)) / (time_increment - 1);
  this->z = (time_increment * m * S * (x + 1.6)) / (time_increment * m - 1);
  this->e = e;
  this->S = S;
  this->m = m;
}

void HindmarshRose::calculate() {
  float value = 0;
  if (this->synaptic) {
    // TODO: Add the synaptic calculation
  }
  float aux_x, aux_y, aux_z;

  aux_x = x + time_increment * (y + 3 * x * x - x * x * x - z + e);
  aux_y = y + time_increment * (1 - 5 * x * x - y);
  aux_z = z + time_increment * m * (-z + S * (x + 1.6));

  this->x = aux_x;
  this->y = aux_y;
  this->z = aux_z;
  this->time += this->time_increment;
}
void HindmarshRose::free() { delete this; }
