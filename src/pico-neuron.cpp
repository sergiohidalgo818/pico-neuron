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

#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define TIME_INCREMENT 0.001
int main() {

  std::string model_name = MODEL_NAME;
  std::string response = RESPONSE;
  float threshold = atof(THRESHOLD);
  bool synaptic = SYNAPTIC;
  std::vector<double> x;
  std::vector<double> t;
  char buffer[32];

  const std::vector<float> ordered_params = []() {
    std::vector<float> result;
    std::string params(ORDERED_PARAMS);

    size_t start = 0;
    size_t end = params.find(',');

    while (end != std::string::npos) {
      std::string token = params.substr(start, end - start);
      result.push_back(std::stof(token));

      start = end + 1;
      end = params.find(',', start);
    }

    if (start < params.size()) {
      std::string token = params.substr(start);
      result.push_back(std::stof(token));
    }

    return result;
  }();
  HindmarshRose *model =
      new HindmarshRose(synaptic, 0, TIME_INCREMENT, ordered_params[0],
                        ordered_params[1], ordered_params[2], ordered_params[3],
                        ordered_params[4], ordered_params[5]);

  while (true) {
    model->calculate();
    sprintf(buffer, "%.5f\n", model->x);
  }
}
