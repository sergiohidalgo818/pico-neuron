/**
 * @file pico-neuron-c.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Main rutine for the pico-neuron program
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#include "ConfigFile/ConfigFile.hpp"
#include "pico/stdlib.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  auto config = ConfigFile::read_config("./config.cfg");

  std::string model_name = config["model_name"];
  bool synaptical = (config["synaptical"] == "true");
  std::string response = config["response"];
  float threshold = std::stof(config["threshold"]);

  std::vector<float> ordered_params =
      ConfigFile::string_to_vector(config["ordered_params"]);

  stdio_init_all();

  std::cout << model_name << std::endl;
  std::cout << synaptical << std::endl;
  std::cout << response << std::endl;
  std::cout << threshold << std::endl;

  std::cout << "Converted values: ";
  for (const auto &value : ordered_params) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}
