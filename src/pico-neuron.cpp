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
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define TIME_INCREMENT 0.001
void uart_init_custom() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
  gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
  uart_set_hw_flow(UART_ID, false, false);
  uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
  uart_set_fifo_enabled(UART_ID, true);
}

int main() {

  std::string model_name = MODEL_NAME;
  std::string response = RESPONSE;
  float threshold = atof(THRESHOLD);
  bool synaptic = SYNAPTIC;
  std::vector<double> x;
  std::vector<double> t;
  char buffer[50];

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

  stdio_init_all();
  uart_init_custom();

  while (true) {
    model->calculate();
    sprintf(buffer, "%.5f\n", model->x);
    uart_puts(UART_ID, buffer);
  }
}
