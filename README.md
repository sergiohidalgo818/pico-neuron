# Pico Neuron

Repository that implements a C/C++ program for using the Raspberry Pi Pico as a "neuron". This means that the Raspberry Pi Pico itself reproduces the behavior of a neural model.

## Description

This repository provides code to turn a Raspberry Pi Pico microcontroller into a hardware neuron simulator, mimicking neural model behavior directly on the device.

## Features

- Written in C/C++ for the Raspberry Pi Pico
- Simulates neural models in real-time

## Getting Started

### Prerequisites

- Raspberry Pi Pico microcontroller (Pico 2 and Pico W)
- C/C++
- gcc-arm-none-eabi


### Configuration

Under the `config/` folder, there are the configuration for each board, feel free to modify it. The name of the folder share the board used in the **PicoSDK** compilation. You can try to create the configuration and test the program for other boards.

Inside each folder, there are several configuration files for each model and its variants.

### Building

```sh
git clone https://github.com/sergiohidalgo818/pico-neuron.git
cd pico-neuron
cmake -B build . -DBOARD_NAME=pico2 -DMODEL_NAME=hindmarsh_rose 
```

The default board is `pico2`, options are `pico2` and `pico_w`
The default model is `hindmarsh_rose`, and options are `hindmarsh_rose` and `hindmarsh_rose_mod`, append `_chaotic` for the chaotic mode (but you can simply modify the parameter inside the config file) and `_syn` for enabling synapsis (**Warning:** Synapse under development)

### Usage

Modify the config files under Defau directory.

## TODO
- Change frequency behaviour (or name)
- Check if fs are needed on cfg files (probably not)
- Check if there is improvement changing the floats to integers (and precision loss)
- Manuel, adjust neuron speed
