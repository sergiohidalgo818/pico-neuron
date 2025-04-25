
cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
set(PICOTOOL_FETCH_FROM_GIT_PATH ${CMAKE_BINARY_DIR}/_deps)
set(PICO_CXX_ENABLE_EXCEPTIONS off)

set (CODE_SOURCE_DIR src)
set (CODE_HEADERS_DIR inc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_neuron_config.cmake)
include(pico_sdk_import.cmake)

project(pico-neuron-c DESCRIPTION "Program that runs a neural model in a Raspberry Pico" LANGUAGES C CXX ASM)

pico_sdk_init()


set(SOURCES
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/pico-neuron-c.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/Model.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/HindmarshRose.cpp
)

# Define your header files
set(HEADERS
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/default.hpp 
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/Model.hpp
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/HindmarshRose.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
    ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
  DECIMAL_PRECISION=${DECIMAL_PRECISION_VALUE}
  MODEL_NAME=${MODEL_NAME_VALUE}
  SYNAPTICAL=${SYNAPTICAL_VALUE}
  RESPONSE=${RESPONSE_VALUE}
  THRESHOLD=${THRESHOLD_VALUE}
  ORDERED_PARAMS=${ORDERED_PARAMS_VALUE}
)

# no_flash means the target is to run from RAM
# pico_set_binary_type(pico-neuron-c no_flash)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico-neuron-c 1)
# pico_enable_stdio_usb(pico-neuron-c 0)


# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR})

# Add any user requested libraries
target_link_libraries(
        ${PROJECT_NAME} 
        pico_stdlib
        hardware_uart
        hardware_timer
        )

pico_add_extra_outputs(${PROJECT_NAME})

