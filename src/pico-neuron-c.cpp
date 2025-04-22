/**
 * @file pico-neuron-c.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Main rutine for the pico-neuron program
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#include "default.hpp"
#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char **argv) {

  std::string model_name = MODEL_NAME;

  bool synaptic = SYNAPTIC;
  std::string response = RESPONSE;
  float threshold = THRESHOLD;

  std::vector<float> ordered_params = {ORDERED_PARAMS};

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
}
