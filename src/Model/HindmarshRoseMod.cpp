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
#include <cmath>
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

HindmarshRoseMod::HindmarshRoseMod(bool synaptic, float initial_time,
                                   float time_increment, float x, float y,
                                   float z, float e, float S, float m, float v,
                                   float gsync, float Sfast, float Esyn,
                                   float Vfast)
    : HindmarshRose(synaptic, initial_time, time_increment, x, y, z, e, S, m,
                    gsync, Sfast, Esyn, Vfast) {

  this->v = v;
}

float HindmarshRoseMod::calculate() {
  float isyn = 0;
  if (this->synaptic && this->recived_value != END_VALUE) {
    float isyn =
        (gsync * (x - esyn)) / (1 + std::exp(sfast * (vfast - recived_value)));
  }
  const float x_sq = x * x;

  const float dx = y + 3.0f * x_sq - x_sq * x - z + e + isyn;
  const float dy = 1.0f - 5.0f * x_sq - y;
  const float dz = m * (-v * z + S * (x + 1.6f));

  x += time_increment * dx;
  y += time_increment * dy;
  z += time_increment * dz;

  time += time_increment;

  return x;
}
void HindmarshRoseMod::free() { delete this; }
