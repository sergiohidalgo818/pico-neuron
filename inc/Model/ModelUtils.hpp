/**
 * @file ModelUtils.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that contains tools for the models selection.
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#ifndef MODEL_UTILS_H
#define MODEL_UTILS_H
#include "ModelType.hpp"
#include <set>
#include <string>
/**
 * @class ModelType
 * @brief Model enumeration
 *
 * Model enumeration for the selection of the model
 *
 */
class ModelUtils {
public:
  static std::set<std::string> get_model_strings();
  static ModelType get_model_by_string(std::string model_name);
};
#endif /* MODEL_UTILS_H */
