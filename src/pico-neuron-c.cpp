#include <stdio.h>

#include "hardware/timer.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
  printf("Hello, world!\n");
  return 0;
}

int main() {
  stdio_init_all();

  // Timer example code - This example fires off the callback after 2000ms
  add_alarm_in_ms(2000, alarm_callback, NULL, false);
  while (true) {
  }
}
