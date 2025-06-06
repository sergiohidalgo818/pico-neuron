# Pico Neuron

Repository that implements a C/C++ program for using the Raspberry Pi Pico as a "neuron". This means that the Raspberry Pi Pico itself reproduces the behavior of a neural model.

## Description

This repository provides code to turn a Raspberry Pi Pico microcontroller into a hardware neuron simulator, mimicking neural model behavior directly on the device.

## Features

- Written in C/C++ for the Raspberry Pi Pico
- Simulates neural models in real-time

## Getting Started

### Prerequisites

- Raspberry Pi Pico microcontroller
- C/C++ toolchain (such as GCC or the Raspberry Pi Pico SDK)

### Building

```sh
git clone https://github.com/sergiohidalgo818/pico-neuron.git
cd pico-neuron
cmake -B build . -DBOARD_NAME=pico_2 # Default is pico_2, options are pico_2 and pico_w
```

### Usage

Modify the config files under `config/` directory.

## TODO
- Change frequency behaviour (or name)
- Check if fs are needed on cfg files (probably not)
- Check if there is improvement changing the floats to integers (and precision loss)
- Manuel, adjust neuron speed
