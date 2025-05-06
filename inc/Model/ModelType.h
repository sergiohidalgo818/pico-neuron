/**
 * @file ModelType.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that contains the enum for the models selection.
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#ifndef MODEL_TYPE_H
#define MODEL_TYPE_H

#define MODEL_COUNT 6
/**
 * @enum ModelType
 * @brief Model enumeration for selecting different models
 *
 * This enumeration provides identifiers for the different
 * model types available in the system.
 */
typedef enum {
  MODEL_HINDMARSH_ROSE,             /**< Basic Hindmarsh-Rose model */
  MODEL_HINDMARSH_ROSE_CHAOTIC,     /**< Chaotic Hindmarsh-Rose model */
  MODEL_HINDMARSH_ROSE_MOD,         /**< Modified Hindmarsh-Rose model */
  MODEL_HINDMARSH_ROSE_MOD_CHAOTIC, /**< Chaotic modified Hindmarsh-Rose */
  MODEL_RULKOV_MAP,                 /**< Rulkov map model */
  MODEL_CUSTOM                      /**< Custom user-defined model */
} ModelType;

static const char *MODEL_TYPE_STRINGS[] = {
    "hindmarsh-rose",     "hindmarsh-rose-chaotic",
    "hindmarsh-rose-mod", "hindmarsh-rose-mod-chaotic",
    "rulkov-map",         "custom"};

/**
 * @brief Convert string to ModelType enum
 * @param str String representation of the model
 * @return Corresponding ModelType or MODEL_UNKNOWN if not found
 */
ModelType model_type_from_string(const char *str);

/**
 * @brief Convert ModelType enum to string
 * @param type The model type enum
 * @return String representation or NULL if invalid
 */
const char *model_type_to_string(ModelType type);

#endif /* MODEL_TYPE_H */
