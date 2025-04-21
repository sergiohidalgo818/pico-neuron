
cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
set(PICOTOOL_FETCH_FROM_GIT_PATH ${CMAKE_BINARY_DIR} )

set (CODE_SOURCE_DIR src)
set (CODE_HEADERS_DIR inc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-neuron-c DESCRIPTION "Program that runs a neural model in a Raspberry Pico" LANGUAGES C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/pico-neuron-c.cpp )

# no_flash means the target is to run from RAM
pico_set_binary_type(pico-neuron-c no_flash)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-neuron-c 1)
pico_enable_stdio_usb(pico-neuron-c 0)

# Add the standard library to the build
target_link_libraries( ${PROJECT_NAME}
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR})

# Add any user requested libraries
target_link_libraries(
        ${PROJECT_NAME} 
        pico_stdlib
        hardware_timer
        )

pico_add_extra_outputs(${PROJECT_NAME})

