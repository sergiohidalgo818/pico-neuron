/**
 * @file ModelType.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that contains the enum for the models selection.
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#ifndef MODEL_TYPE_HPP
#define MODEL_TYPE_HPP
/**
 * @class ModelType
 * @brief Model enumeration
 *
 * Model enumeration for the selection of the model
 *
 */
enum class ModelType {
  Hindmarsh_Rose,
  Hindmarsh_Rose_Syn,
  Hindmarsh_Rose_Chaotic,
  Hindmarsh_Rose_Chaotic_Syn,
  Hindmarsh_Rose_Mod,
  Hindmarsh_Rose_Mod_Syn,
  Hindmarsh_Rose_Mod_Chaotic,
  Hindmarsh_Rose_Mod_Chaotic_Syn,
  Rulkov_Map,
  Custom
};

#endif /* MODEL_TYPE_HPP */
