
cmake_minimum_required(VERSION 3.13)


set (CODE_SOURCE_DIR src)
set (CODE_HEADERS_DIR inc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")
project(pico-neuron DESCRIPTION "Program that runs a neural model in a Raspberry Pico" LANGUAGES C CXX ASM)
include(pico_neuron_config.cmake)


set(SOURCES
    ${PROJECT_SOURCE_DIR}/${CODE_SOURCE_DIR}/pico-neuron.cpp
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

add_definitions(-DDECIMAL_PRECISION="${DECIMAL_PRECISION}")
add_definitions(-DMODEL_NAME="${MODEL_NAME}")
add_definitions(-DSYNAPTICAL="${SYNAPTICAL}")
add_definitions(-DRESPONSE="${RESPONSE}")
add_definitions(-DTHRESHOLD="${THRESHOLD}")
add_definitions(-DORDERED_PARAMS="${ORDERED_PARAMS}")
add_definitions(-DPICO_DEFAULT_CPU_CLOCK=250000000)

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
)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR}/${CODE_HEADERS_DIR})

# Add any user requested libraries
target_link_libraries(
        ${PROJECT_NAME} 
    -Wl,--start-group
    -Wl,--end-group

        )




