/**
 * @file HindmarshRoseMod.cpp
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in c++ for the class of HindmarshRoseMod class
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Model/HindmarshRoseMod.hpp"
#include "Model/HindmarshRose.hpp"

HindmarshRoseMod::HindmarshRoseMod(bool synaptic, float initial_time,
                                   float time_increment, float x, float y,
                                   float z, float e, float S, float m, float v)
    : HindmarshRose(synaptic, initial_time, time_increment, x, y, z, e, S, m) {
  this->v = v;
}

HindmarshRoseMod::HindmarshRoseMod(bool synaptic, float threshold,
                                   float initial_time, float time_increment,
                                   float x, float y, float z, float e, float S,
                                   float m, float v)
    : HindmarshRose(synaptic, threshold, initial_time, time_increment, x, y, z,
                    e, S, m) {
  this->v = v;
}

float HindmarshRoseMod::calculate() {
  float value = 0;
  if (this->synaptic) {
    // TODO: Add the synaptic calculation
  }
  float aux_x, aux_y, aux_z;

  aux_x = x + time_increment * (y + 3 * x * x - x * x * x - z + e);
  aux_y = y + time_increment * (1 - 5 * x * x - y);
  aux_z = z + time_increment * m * (-v * z + S * (x + 1.6));

  this->x = aux_x;
  this->y = aux_y;
  this->z = aux_z;
  this->time += this->time_increment;

  return this->x;
}
void HindmarshRoseMod::free() { delete this; }
