/**
 * @file pico-neuron-c.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Main rutine for the pico-neuron program
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#include "Model/HindmarshRose.h"
#include "default.h"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "pico/stdlib.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UART_ID uart0
#define BAUD_RATE 1000000
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define END_VALUE -9999.0f
#define MAX_PARAMS 10
#define BUFFER_SIZE 32

void uart_init_custom() {
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
  uart_set_hw_flow(UART_ID, false, false);
  uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
  uart_set_fifo_enabled(UART_ID, true);
}

void parse_ordered_params(float params[], int *param_count) {
  const char *ordered_params = ORDERED_PARAMS;
  char *token;
  char *rest = (char *)ordered_params;
  *param_count = 0;

  while ((token = strtok_r(rest, ",", &rest))) {
    if (*param_count >= MAX_PARAMS)
      break;
    params[(*param_count)++] = atof(token);
  }
}

__not_in_flash("main_loop") void main_loop() {
  const float decimal_precision = DECIMAL_PRECISION;
  const char *model_name = MODEL_NAME;
  const char *response = RESPONSE;
  const float threshold = THRESHOLD;
  const bool synaptic = SYNAPTIC;
  const float time_increment = TIME_INCREMENT;
  const float frequency = FREQUENCY;

  float ordered_params[MAX_PARAMS];
  int param_count = 0;
  parse_ordered_params(ordered_params, &param_count);

  HindmarshRose *model = NULL;

  /* switch (model_type) { */
  /* case Hindmarsh_Rose: */
  /* case Hindmarsh_Rose_Chaotic: */
  model = HindmarshRose_init(synaptic, 0, time_increment, ordered_params[0],
                             ordered_params[1], ordered_params[2],
                             ordered_params[3], ordered_params[4],
                             ordered_params[5]);
  /*   break; */
  /**/
  /* case Hindmarsh_Rose_Mod: */
  /* case Hindmarsh_Rose_Mod_Chaotic: */
  /*     model = (Model *)HindmarshRoseMod_create( */
  /*         synaptic, 0, time_increment, ordered_params[0], ordered_params[1],
   */
  /*         ordered_params[2], ordered_params[3], ordered_params[4], */
  /*         ordered_params[5], ordered_params[6]); */
  /*   break; */
  /**/
  /* default: */
  /*   model = (Model *)HindmarshRose_init(synaptic, 0, time_increment, */
  /*                                         ordered_params[0],
   * ordered_params[1], */
  /*                                         ordered_params[2],
   * ordered_params[3], */
  /*                                         ordered_params[4],
   * ordered_params[5]); */
  /*   break; */
  /* } */

  if (!model) {
    // Handle model creation failure
    return;
  }

  float counter = frequency;
  while (true) {
    float value;
    value = HindmarshRose_calculate(model);
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

  HindmarshRose_free(model);
}

__not_in_flash("write_loop") void write_loop() {
  char buffer[BUFFER_SIZE];
  while (true) {
    uint32_t received = multicore_fifo_pop_blocking();
    float received_float;
    memcpy(&received_float, &received, sizeof(received_float));

    if (received_float == END_VALUE) {
      break;
    }

    int len = snprintf(buffer, BUFFER_SIZE, "%.5f\n", received_float);
    uart_write_blocking(UART_ID, (const uint8_t *)buffer, len);
  }

  int len = snprintf(buffer, BUFFER_SIZE, "END\n");
  uart_write_blocking(UART_ID, (const uint8_t *)buffer, len);
}

int main() {
  stdio_init_all();
  uart_init_custom();
  multicore_launch_core1(main_loop);
  write_loop();
  return 0;
}
