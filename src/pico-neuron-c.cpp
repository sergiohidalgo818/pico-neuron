/**
 * @file pico-neuron-c.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Main rutine for the pico-neuron program
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#include "Model/HindmarshRose.hpp"
#include "Model/ModelUtils.hpp"
#include "default.hpp"
#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::string model_name = MODEL_NAME;

  bool synaptic = SYNAPTIC;
  std::string response = RESPONSE;
  float threshold = THRESHOLD;

  std::vector<float> ordered_params = {ORDERED_PARAMS};

  HindmarshRose *model = new HindmarshRose(synaptic, ordered_params, 0, 0.001);

  stdio_init_all();

  std::cout << model_name << std::endl;
  std::cout << synaptic << std::endl;
  std::cout << response << std::endl;
  std::cout << threshold << std::endl;

  std::cout << "Converted values: ";
  for (const auto &value : ordered_params) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  for (int i = 0; i < 4000; i++) {
    model->calculate();
    std::cout << model->x << " ";
    std::cout << model->y << " ";
    std::cout << model->z << " ";
    std::cout << model->time << std::endl;
  }
}
