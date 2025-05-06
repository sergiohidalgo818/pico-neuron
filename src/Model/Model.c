/**
 * @file Model.c
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in C for the Model struct
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Model/Model.h"
#include <stdlib.h>

Model *Model_create(bool synaptic, float initial_time, float time_increment) {
  Model *self = (Model *)malloc(sizeof(Model));
  if (!self)
    return NULL;

  self->synaptic = synaptic;
  self->threshold = 0.0f;
  self->recived_value = 0.0f;
  self->time = initial_time;
  self->time_increment = time_increment;
  self->output_value = 0.0f;

  return self;
}

Model *Model_createWithThreshold(bool synaptic, float threshold,
                                 float initial_time, float time_increment) {
  Model *self = (Model *)malloc(sizeof(Model));
  if (!self)
    return NULL;

  self->synaptic = synaptic;
  self->threshold = threshold;
  self->recived_value = 0.0f;
  self->time = initial_time;
  self->time_increment = time_increment;
  self->output_value = 0.0f;

  return self;
}

void Model_interact(Model *self, float recived_value) {
  if (!self)
    return;

  self->recived_value = recived_value;
}

float Model_calculate(Model *self) {
  if (!self && !self->calculate && !self->inherited_model)
    return 0.0f;

  return self->calculate(self->inherited_model);
}

void Model_destroy(Model *self) {
  if (self) {
    free(self);
  }
}
