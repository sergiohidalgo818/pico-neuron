
cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
set(PICOTOOL_FETCH_FROM_GIT_PATH ${CMAKE_BINARY_DIR}/_deps)
set(FREERTOS_FETCH_FROM_GIT on)
set(PICO_CXX_ENABLE_EXCEPTIONS off)

set (CODE_SOURCE_DIR src)
set (CODE_HEADERS_DIR inc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED BOARD_NAME)
    set(BOARD_NAME pico2)
endif()

set(PICO_BOARD ${BOARD_NAME} CACHE STRING "Board type")
include(pico_sdk_import.cmake)
project(pico-neuron DESCRIPTION "Program that runs a neural model in a Raspberry Pico" LANGUAGES C CXX ASM)
include(pico_neuron_config.cmake)

pico_sdk_init()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/pico-neuron.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/Model.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/ModelUtils.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/HindmarshRose.cpp
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/Model/HindmarshRoseMod.cpp
)

# Define your header files
set(HEADERS
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/default.hpp 
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/Model.hpp
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/ModelType.hpp
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/ModelUtils.hpp
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/HindmarshRose.hpp
  ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}/Model/HindmarshRoseMod.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR} 
    ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR}
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}
)

target_compile_definitions(pico-neuron PRIVATE
    DECIMAL_PRECISION=${DECIMAL_PRECISION}
    MODEL_NAME="${MODEL_NAME}"
    SYNAPTICAL=${SYNAPTICAL}
    RESPONSE="${RESPONSE}"
    THRESHOLD=${THRESHOLD}
    TIME_INCREMENT=${TIME_INCREMENT}
    FREQUENCY=${FREQUENCY}
    ORDERED_PARAMS="${ORDERED_PARAMS}"
    PICO_DEFAULT_CPU_CLOCK=250000000
)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    -fno-exceptions 
    -fno-check-new 
    $<$<COMPILE_LANGUAGE:CXX>:-fno-enforce-eh-specs>
    -g 
    -ffunction-sections 
    -fdata-sections 
    -O3
    -funroll-loops 
    -Werror 
    -Wall
    -flto
    -ffast-math
    -mcpu=cortex-m0plus
    -mthumb
)
# no_flash means the target is to run from RAM
# pico_set_binary_type ( ${PROJECT_NAME} no_flash)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)


# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR})

# Add any user requested libraries
target_link_libraries(
        ${PROJECT_NAME} 
        pico_stdlib
        hardware_uart
        hardware_dma
        pico_multicore
    -Wl,--start-group
    stdc++_nano
    -Wl,--end-group

        )

target_link_options(${PROJECT_NAME} PRIVATE

    --specs=nano.specs
    --specs=nosys.specs
)

pico_add_extra_outputs(${PROJECT_NAME})

