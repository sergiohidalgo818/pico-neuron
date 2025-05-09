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
#include <cmath>

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

  this->gsync = 0.241;
  this->Sfast = 0.44;
  this->Esyn = -1.92;
  this->Vfast = -1.66;
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

  this->gsync = 0.241;
  this->Sfast = 0.44;
  this->Esyn = -1.92;
  this->Vfast = -1.66;
}

float HindmarshRose::calculate() {
  float Isyn = 0;
  if (this->synaptic && this->recived_value != END_VALUE) {
    float Isyn =
        (gsync * (x - Esyn)) / (1 + std::exp(Sfast * (Vfast - recived_value)));
  }
  const float x_sq = x * x;

  const float dx = y + 3.0f * x_sq - x_sq * x - z + e + Isyn;
  const float dy = 1.0f - 5.0f * x_sq - y;
  const float dz = m * (-z + S * (x + 1.6f));

  x += time_increment * dx;
  y += time_increment * dy;
  z += time_increment * dz;

  time += time_increment;

  return x;
}
void HindmarshRose::free() { delete this; }
