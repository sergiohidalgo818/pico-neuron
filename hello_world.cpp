#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "hardware/watchdog.h"
#include "pico/stdlib.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
  // Put your timeout handler code in here
  return 0;
}

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for
// information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

int main() {
  stdio_init_all();

  // Interpolator example code
  interp_config cfg = interp_default_config();
  // Now use the various interpolator library functions for your use case
  // e.g. interp_config_clamp(&cfg, true);
  //      interp_config_shift(&cfg, 2);
  // Then set the config
  interp_set_config(interp0, 0, &cfg);
  // For examples of interpolator use see
  // https://github.com/raspberrypi/pico-examples/tree/master/interp

  // Timer example code - This example fires off the callback after 2000ms
  add_alarm_in_ms(2000, alarm_callback, NULL, false);
  // For more examples of timer use see
  // https://github.com/raspberrypi/pico-examples/tree/master/timer

  // Watchdog example code
  if (watchdog_caused_reboot()) {
    printf("Rebooted by Watchdog!\n");
    // Whatever action you may take if a watchdog caused a reboot
  }

  // Enable the watchdog, requiring the watchdog to be updated every 100ms or
  // the chip will reboot second arg is pause on debug which means the watchdog
  // will pause when stepping through code
  watchdog_enable(100, 1);

  // You need to call this function at least more often than the 100ms in the
  // enable call to prevent a reboot
  watchdog_update();

  printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
  printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
  // For more examples of clocks use see
  // https://github.com/raspberrypi/pico-examples/tree/master/clocks

  // Set up our UART
  uart_init(UART_ID, BAUD_RATE);
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // Use some the various UART functions to send out data
  // In a default system, printf will also output via the default UART

  // Send out a string, with CR/LF conversions
  uart_puts(UART_ID, " Hello, UART!\n");

  // For more examples of UART use see
  // https://github.com/raspberrypi/pico-examples/tree/master/uart

  while (true) {
    printf("Hello, world!\n");
    sleep_ms(1000);
  }
}
