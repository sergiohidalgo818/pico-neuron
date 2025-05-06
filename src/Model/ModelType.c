/**
 * @file ModelType.c
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in C for the Model type.
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Model/ModelType.h"
#include <string.h>

ModelType model_type_from_string(const char *str) {
  if (!str)
    return MODEL_HINDMARSH_ROSE;

  for (int i = 0; i < MODEL_COUNT; i++) {
    if (strcasecmp(str, MODEL_TYPE_STRINGS[i]) == 0) {
      return (ModelType)i;
    }
  }
  return MODEL_HINDMARSH_ROSE;
}

const char *model_type_to_string(ModelType type) {
  if (type < 0 || type >= MODEL_COUNT) {
    return NULL;
  }
  return MODEL_TYPE_STRINGS[type];
}
