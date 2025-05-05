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
#include "class/cdc/cdc_device.h"
#include "default.hpp"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "tusb.h" // General TinyUSB include
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define TIME_INCREMENT 0.005
#define END_VALUE -9999.0f

// Write a 32-bit float to USB directly, no printf needed
void usb_write_float(float value) {
  uint32_t data = *(uint32_t *)&value; // Convert float to uint32
  tud_cdc_n_write(0, (uint8_t *)&data, sizeof(data));
  tud_cdc_n_write_flush(0); // Flush to ensure data is sent immediately
}
__not_in_flash("main_loop") void main_loop() {
  std::string model_name = MODEL_NAME;
  std::string response = RESPONSE;
  float threshold = atof(THRESHOLD);
  bool synaptic = SYNAPTIC;
  std::vector<double> x;
  std::vector<double> t;
  char buffer[32];

  // Initializing model with ordered_params
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

  // Instantiate model
  HindmarshRose *model =
      new HindmarshRose(synaptic, 0, TIME_INCREMENT, ordered_params[0],
                        ordered_params[1], ordered_params[2], ordered_params[3],
                        ordered_params[4], ordered_params[5]);

  // Main computation loop
  while (true) {
    model->calculate();
    uint32_t bits;

    memcpy(&bits, &model->x, sizeof(bits));
    multicore_fifo_push_blocking(bits); // Send data to core 1

    if (model->time >= 500) {
      break;
    }
  }

  uint32_t end_bits;
  float end = END_VALUE;
  memcpy(&end_bits, &end, sizeof(end_bits));

  multicore_fifo_push_blocking(end_bits); // Send data to core 1
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
    usb_write_float(received_float); // Print data received from core 0 }
  }
  printf("END\n");
}

int main() {
  stdio_usb_init(); // Initialize USB for communication
  // Launch main_loop on core 1
  multicore_launch_core1(main_loop);

  // Run write_loop on core 0
  write_loop();
}
