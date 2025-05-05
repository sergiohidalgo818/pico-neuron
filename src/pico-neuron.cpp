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
#include "Model/HindmarshRoseMod.hpp"
#include "Model/ModelType.hpp"
#include "Model/ModelUtils.hpp"
#include "default.hpp"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

#include <cstring>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define UART_ID uart0
#define BAUD_RATE 1000000
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define END_VALUE -9999.0f

void uart_init_custom() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
  gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
  uart_set_hw_flow(UART_ID, false, false);
  uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
  uart_set_fifo_enabled(UART_ID, true);
}

__not_in_flash("main_loop") void main_loop() {

  constexpr float decimal_precision = DECIMAL_PRECISION;
  constexpr const char *model_name = MODEL_NAME;
  constexpr const char *response = RESPONSE;
  constexpr float threshold = THRESHOLD;
  constexpr bool synaptic = SYNAPTIC;
  constexpr float time_increment = TIME_INCREMENT;
  constexpr float frequency = FREQUENCY;
  char buffer[32];
  float counter = frequency;
  Model *model;
  ModelType model_type = ModelUtils::get_model_by_string(model_name);
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

  switch (model_type) {
  case ModelType::Hindmarsh_Rose:
  case ModelType::Hindmarsh_Rose_Chaotic:
    model = new HindmarshRose(synaptic, 0, TIME_INCREMENT, ordered_params[0],
                              ordered_params[1], ordered_params[2],
                              ordered_params[3], ordered_params[4],
                              ordered_params[5]);
    break;

  case ModelType::Hindmarsh_Rose_Mod:
  case ModelType::Hindmarsh_Rose_Mod_Chaotic:
    model = new HindmarshRoseMod(synaptic, 0, TIME_INCREMENT, ordered_params[0],
                                 ordered_params[1], ordered_params[2],
                                 ordered_params[3], ordered_params[4],
                                 ordered_params[5], ordered_params[6]);
  default:
    model = new HindmarshRose(synaptic, 0, TIME_INCREMENT, ordered_params[0],
                              ordered_params[1], ordered_params[2],
                              ordered_params[3], ordered_params[4],
                              ordered_params[5]);
    break;
  }

  while (true) {
    float value = model->calculate();
    uint32_t bits;

    memcpy(&bits, &value, sizeof(bits));
    if (multicore_fifo_wready() && counter <= decimal_precision) {
      multicore_fifo_push_blocking(bits);
      counter = frequency;
    }

    counter -= 1;

    if (model->time >= 10000) {
      break;
    }
  }
  uint32_t end_bits;
  float end = END_VALUE;

  memcpy(&end_bits, &end, sizeof(end_bits));
  multicore_fifo_push_blocking(end_bits);
}

__not_in_flash("write_loop") void write_loop() {
  char buffer[32];
  int len;
  while (true) {
    uint32_t received = multicore_fifo_pop_blocking();
    float received_float;

    memcpy(&received_float, &received, sizeof(received_float));

    if (received_float == END_VALUE) {
      break;
    }
    len = sprintf(buffer, "%.5f\n", received_float);
    uart_write_blocking(UART_ID, (const uint8_t *)buffer, len);
  }
  len = sprintf(buffer, "END\n");
  uart_write_blocking(UART_ID, (const uint8_t *)buffer, len);
}
int main() {

  stdio_init_all();
  uart_init_custom();
  multicore_launch_core1(main_loop);
  write_loop();
}
