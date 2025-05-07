/**
 * @file fixed_utils.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that contains the utils for float to fixed transformations.
 * @version 0.1
 * @date 2025-05-07
 *
 * @copyright Copyright (c) 2025
 */

#ifndef FIXED_UTILS_H
#define FIXED_UTILS_H
#include <cstdint>

#define FP_SHIFT 16
#define FP_ONE (1 << FP_SHIFT)

inline int32_t float_to_fixed(float f) {
  return static_cast<int32_t>(f * FP_ONE);
}

inline float fixed_to_float(int32_t f) {
  return static_cast<float>(f) / FP_ONE;
}

inline int32_t fp_mul(int32_t a, int32_t b) {
  return static_cast<int32_t>((static_cast<int64_t>(a) * b) >> FP_SHIFT);
}

inline int32_t fp_div(int32_t a, int32_t b) {
  return static_cast<int32_t>((static_cast<int64_t>(a) << FP_SHIFT) / b);
}

#endif
