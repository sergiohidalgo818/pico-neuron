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
  this->y = 1.0f - 5.0f * x * x;
  this->z = S * (x + 1.6f);
  this->e = e;
  this->S = S;
  this->m = m;
}

HindmarshRose::HindmarshRose(bool synaptic, float threshold, float initial_time,
                             float time_increment, float x, float y, float z,
                             float e, float S, float m)
    : Model(synaptic, threshold, initial_time, time_increment) {
  this->x = x;
  this->y = 1.0f - 5.0f * x * x;
  this->z = S * (x + 1.6f);
  this->e = e;
  this->S = S;
  this->m = m;
}

float HindmarshRose::calculate() {
  if (this->synaptic) {
    // TODO: Add the synaptic calculation
  }
  const float x_sq = x * x;

  const float dx = y + 3.0f * x_sq - x_sq * x - z + e;
  const float dy = 1.0f - 5.0f * x_sq - y;
  const float dz = m * (-z + S * (x + 1.6f));

  x += time_increment * dx;
  y += time_increment * dy;
  z += time_increment * dz;

  time += time_increment;

  return x;
}
void HindmarshRose::free() { delete this; }
