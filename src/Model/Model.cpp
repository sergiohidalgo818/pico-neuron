/**
 * @file Model.cpp
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in c++ for the class of Model class
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Model/Model.hpp"

Model::Model(bool synaptic, float initial_time, float time_incremet) {
  this->synaptic = synaptic;
  this->threshold = 0.0;
  this->recived_value = END_VALUE;
  this->time = initial_time;
  this->time_increment = time_incremet;
}

Model::Model(bool synaptic, float threshold, float initial_time,
             float time_incremet) {
  this->synaptic = synaptic;
  this->threshold = threshold;
  this->recived_value = END_VALUE;
  this->time = initial_time;
  this->time_increment = time_incremet;
}

void Model::interact(float recived_value) {
  this->recived_value = recived_value;
}

void Model::free() { delete this; }
