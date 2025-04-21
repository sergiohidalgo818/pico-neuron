cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(pico-neuron-c C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hello_world
    hello_world.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)

include_directories(
  ~/.pico-sdk/toolchain/14_2_Rel1/arm-none-eabi/include
  ~/.pico-sdk/toolchain/14_2_Rel1/arm-none-eabi/include/c++/14.2.1
  ~/.pico-sdk/toolchain/14_2_Rel1/arm-none-eabi/include/c++/14.2.1/arm-none-eabi
  ~/.pico-sdk/sdk/2.1.1/src/rp2_common/hardware_pwm
  ~/.pico-sdk/sdk/2.1.1/src/rp2_common/hardware_interp/include
)
