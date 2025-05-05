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
#include "hardware/dma.h"
#include "hardware/uart.h"
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
#define TIME_INCREMENT 0.005
#define END_VALUE -9999.0f

void uart_init_custom() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
  gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
  uart_set_hw_flow(UART_ID, false, false);
  uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
  uart_set_fifo_enabled(UART_ID, true);
}
int dma_uart_init() {
  int dma_chan = dma_claim_unused_channel(true);
  dma_channel_config cfg = dma_channel_get_default_config(dma_chan);

  channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
  channel_config_set_read_increment(&cfg, true);
  channel_config_set_write_increment(&cfg, false);
  channel_config_set_dreq(&cfg, uart_get_dreq(UART_ID, true)); // TX DREQ

  dma_channel_configure(dma_chan, &cfg,
                        &uart_get_hw(UART_ID)->dr, // destination: UART FIFO
                        NULL,                      // source will be set later
                        0,                         // length will be set later
                        false                      // don't start yet
  );

  return dma_chan;
}
__not_in_flash("main_loop") void main_loop() {

  std::string model_name = MODEL_NAME;
  std::string response = RESPONSE;
  float threshold = atof(THRESHOLD);
  bool synaptic = SYNAPTIC;
  std::vector<double> x;
  std::vector<double> t;
  char buffer_a[32];
  char buffer_b[32];
  char *active_buffer = buffer_a;
  char *next_buffer = buffer_b;
  int dma_chan = dma_uart_init();
  bool dma_busy = false;

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
    if (model->time >= 500) {
      break;
    }

    int len = snprintf(active_buffer, 32, "%.5f\n", model->x);
    if (dma_busy) {
      dma_channel_wait_for_finish_blocking(dma_chan);
    }

    dma_channel_set_read_addr(dma_chan, active_buffer, false);
    dma_channel_set_trans_count(dma_chan, len, true); // start immediately
    dma_busy = true;
    std::swap(active_buffer, next_buffer);
  }
  if (dma_busy) {
    dma_channel_wait_for_finish_blocking(dma_chan);
  }

  const char *end_msg = "END\n";
  int end_len = strlen(end_msg);
  dma_channel_set_read_addr(dma_chan, end_msg, false);
  dma_channel_set_trans_count(dma_chan, end_len, true);
  dma_channel_wait_for_finish_blocking(dma_chan);

  dma_channel_unclaim(dma_chan);
}

int main() {

  stdio_init_all();
  uart_init_custom();
  main_loop();
}
