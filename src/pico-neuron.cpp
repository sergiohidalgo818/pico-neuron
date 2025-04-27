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
#include "pico/stdlib.h"
#include <string>
#include <vector>

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_TX_PIN 0
#define UART_RX_PIN 1
int main() {

  std::string model_name = MODEL_NAME;
  std::string response = RESPONSE;
  float threshold = THRESHOLD;
  bool synaptic = SYNAPTIC;
  std::vector<float> ordered_params = {ORDERED_PARAMS};

  char buffer[50];

  HindmarshRose *model = new HindmarshRose(synaptic, ordered_params, 0, 0.001);

  // stdio_init_all();

  uart_init(UART_ID, BAUD_RATE);

  gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
  gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));

  while (true) {
    model->calculate();
    sprintf(buffer, "%.5f\n", model->x);
    uart_puts(UART_ID, buffer);
  }
}
