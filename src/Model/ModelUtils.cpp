/**
 * @file ModelUtils.cpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that contains the miplementation of functions of the models enum.
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#include "Model/ModelUtils.hpp"
#include "Model/ModelType.hpp"
#include <map>
#include <strings.h>

const std::map<ModelType, std::string> model_to_str{
    {ModelType::Hindmarsh_Rose, "hindmarsh_rose"},
    {ModelType::Hindmarsh_Rose_Chaotic, "hindmarsh_rose_chaotic"},
    {ModelType::Hindmarsh_Rose_Mod, "hindmarsh_rose_mod"},
    {ModelType::Hindmarsh_Rose_Mod_Chaotic, "hindmarsh_rose_mod_chaotic"},
    {ModelType::Rulkov_Map, "rulkov_map"},
    {ModelType::Custom, "custom"}};

const std::map<std::string, ModelType> str_to_model{
    {"hindmarsh_rose", ModelType::Hindmarsh_Rose},
    {"hindmarsh_rose_chaotic", ModelType::Hindmarsh_Rose_Chaotic},
    {"hindmarsh_rose_mod", ModelType::Hindmarsh_Rose_Mod},
    {"hindmarsh_rose_mod_chaotic", ModelType::Hindmarsh_Rose_Mod_Chaotic},
    {"rulkov_map", ModelType::Rulkov_Map},
    {"custom", ModelType::Custom}};

std::set<std::string> ModelUtils::get_model_strings() {
  std::set<std::string> result;
  for (const auto &[_, str] : model_to_str)
    result.insert(str);
  return result;
}

ModelType ModelUtils::get_model_by_string(std::string model_name) {
  auto it = str_to_model.find(model_name);
  return (it != str_to_model.end()) ? it->second : ModelType::Hindmarsh_Rose;
}
