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
#include "hardware/dma.h"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"

#include <cstring>
#include <numeric>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#define UART_SEND_ID uart0
#define UART_SEND_TX_PIN 0
#define UART_SEND_RX_PIN 1
#define UART_SEND_MIRROR_TX_PIN 17
#define UART_SEND_MIRROR_RX_PIN 16

#define UART_RECIVE_ID uart1
#define UART_RECIVE_TX_PIN 8
#define UART_RECIVE_RX_PIN 9

#define BAUD_RATE 1000000

#define READ_MS 2

void uart_custom_init(uart_inst_t *uart_id, uint tx_pin, uint rx_pin) {
  uart_init(uart_id, BAUD_RATE);
  gpio_set_function(tx_pin, UART_FUNCSEL_NUM(uart_id, tx_pin));
  gpio_set_function(rx_pin, UART_FUNCSEL_NUM(uart_id, rx_pin));
  uart_set_hw_flow(uart_id, false, false);
  uart_set_format(uart_id, 8, 1, UART_PARITY_NONE);
  uart_set_fifo_enabled(uart_id, true);
}

int dma_uart_send_init() {
  int dma_chan = dma_claim_unused_channel(true);
  dma_channel_config cfg = dma_channel_get_default_config(dma_chan);

  channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
  channel_config_set_read_increment(&cfg, true);
  channel_config_set_write_increment(&cfg, false);
  channel_config_set_dreq(&cfg, uart_get_dreq(UART_SEND_ID, true)); // TX DREQ

  dma_channel_configure(
      dma_chan, &cfg,
      &uart_get_hw(UART_SEND_ID)->dr, // destination: UART FIFO
      NULL,                           // source will be set later
      0,                              // length will be set later
      false                           // don't start yet
  );

  return dma_chan;
}

__not_in_flash("read_uart_with_timeout") float read_uart_with_timeout(
    uint timeout_ms) {
  char buffer[32] = "";
  int index = 0;
  absolute_time_t deadline = make_timeout_time_ms(timeout_ms);

  while (absolute_time_diff_us(get_absolute_time(), deadline) > 0) {
    if (uart_is_readable(uart0)) {
      char ch = uart_getc(uart0);
      deadline = make_timeout_time_ms(timeout_ms); // reset timeout on input

      if (ch == '\n') {
        buffer[index] = '\0';
        return atof(buffer);
      } else if (index < sizeof(buffer) - 1) {
        buffer[index++] = ch;
      }
    }
  }

  return END_VALUE;
}

__not_in_flash("measure_average_runtime") double measure_average_runtime(
    Model *model) {
  uint32_t durations[1000];
  size_t count = 0;

  uint64_t start_time = to_us_since_boot(get_absolute_time());

  while (to_us_since_boot(get_absolute_time()) - start_time < 1000000 &&
         count < 1000) {
    uint64_t t0 = to_us_since_boot(get_absolute_time());
    model->calculate();
    uint64_t t1 = to_us_since_boot(get_absolute_time());
    durations[count++] = t1 - t0;
  }

  if (count == 0)
    return 0.0;

  uint64_t total = 0;
  for (size_t i = 0; i < count; ++i)
    total += durations[i];

  return static_cast<double>(total) / count;
}

__not_in_flash("main_loop") void main_loop() {

  constexpr float decimal_precision = DECIMAL_PRECISION;
  constexpr const char *model_name = MODEL_NAME;
  constexpr const char *response = RESPONSE;
  constexpr float threshold = THRESHOLD;
  constexpr bool synaptic = SYNAPTIC;
  constexpr float time_increment = TIME_INCREMENT;
  constexpr int frequency = FREQUENCY;
  char buffer[32];
  int counter = frequency;
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
    model = new HindmarshRose(synaptic, 0, time_increment, ordered_params[0],
                              ordered_params[1], ordered_params[2],
                              ordered_params[3], ordered_params[4],
                              ordered_params[5]);
    break;

  case ModelType::Hindmarsh_Rose_Syn:
  case ModelType::Hindmarsh_Rose_Chaotic_Syn:
    model = new HindmarshRose(
        synaptic, 0, time_increment, ordered_params[0], ordered_params[1],
        ordered_params[2], ordered_params[3], ordered_params[4],
        ordered_params[5], ordered_params[6], ordered_params[7],
        ordered_params[8], ordered_params[9]);
    break;

  case ModelType::Hindmarsh_Rose_Mod:
  case ModelType::Hindmarsh_Rose_Mod_Chaotic:
    model = new HindmarshRoseMod(synaptic, 0, time_increment, ordered_params[0],
                                 ordered_params[1], ordered_params[2],
                                 ordered_params[3], ordered_params[4],
                                 ordered_params[5], ordered_params[6]);

    break;

  case ModelType::Hindmarsh_Rose_Mod_Syn:
  case ModelType::Hindmarsh_Rose_Mod_Chaotic_Syn:
    model = new HindmarshRoseMod(
        synaptic, 0, time_increment, ordered_params[0], ordered_params[1],
        ordered_params[2], ordered_params[3], ordered_params[4],
        ordered_params[5], ordered_params[6], ordered_params[7],
        ordered_params[8], ordered_params[9], ordered_params[10]);
    break;
  default:
    model = new HindmarshRose(synaptic, 0, time_increment, ordered_params[0],
                              ordered_params[1], ordered_params[2],
                              ordered_params[3], ordered_params[4],
                              ordered_params[5]);
    break;
  }

  double micro = measure_average_runtime(model);
  int number_exe = 1 / model->time_increment;

  double micro_rest = 1000000 / (number_exe * micro);
  double sleep_for = micro_rest / number_exe;
  while (true) {
    if (model->synaptic) {
      model->interact(read_uart_with_timeout(READ_MS));
    }
    float value = model->calculate();
    uint32_t bits;

    memcpy(&bits, &value, sizeof(bits));
    if (multicore_fifo_wready()) {
      multicore_fifo_push_blocking(bits);
    }

    sleep_us(sleep_for);
  }
}

__not_in_flash("write_loop") void write_loop() {
  char buffer_a[32];
  char buffer_b[32];
  char *active_buffer = buffer_a;
  char *next_buffer = buffer_b;
  int len;
  int dma_send_chan = dma_uart_send_init();

  while (true) {
    uint32_t received = multicore_fifo_pop_blocking();
    float received_float;

    memcpy(&received_float, &received, sizeof(received_float));

    memset(active_buffer, 0, 32);

    len = snprintf(active_buffer, 32, "%.5f\n", received_float);

    dma_channel_wait_for_finish_blocking(dma_send_chan);

    dma_channel_set_read_addr(dma_send_chan, active_buffer, false);
    dma_channel_set_trans_count(dma_send_chan, len, true);

    std::swap(active_buffer, next_buffer);
  }
}
int main() {

  stdio_init_all();
  uart_custom_init(UART_SEND_ID, UART_SEND_TX_PIN, UART_SEND_RX_PIN);
  uart_custom_init(UART_SEND_ID, UART_SEND_MIRROR_TX_PIN, UART_SEND_RX_PIN);
  uart_custom_init(UART_RECIVE_ID, UART_RECIVE_TX_PIN, UART_RECIVE_RX_PIN);

  multicore_launch_core1(main_loop);
  write_loop();
}
