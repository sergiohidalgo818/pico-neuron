/**
 * @file HindmarshRose.c
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Implementation file in c for the HindmarshRose self
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "Model/HindmarshRose.h"
#include <stdlib.h>

HindmarshRose *HindmarshRose_init(bool synaptic, float initial_time,
                                  float time_increment, float x, float y,
                                  float z, float e, float S, float m) {
  HindmarshRose *self = (HindmarshRose *)malloc(sizeof(HindmarshRose));
  if (!self)
    return NULL;

  self->synaptic = synaptic;
  self->threshold = 0.0f;
  self->recived_value = 0.0f;
  self->time = initial_time;
  self->time_increment = time_increment;

  self->x = x;
  self->y = y;
  self->z = z;
  self->e = e;
  self->S = S;
  self->m = m;

  return self;
}

HindmarshRose *HindmarshRose_initWithThreshold(bool synaptic, float threshold,
                                               float initial_time,
                                               float time_increment, float x,
                                               float y, float z, float e,
                                               float S, float m) {
  HindmarshRose *self = (HindmarshRose *)malloc(sizeof(HindmarshRose));
  if (!self)
    return NULL;

  self->synaptic = synaptic;
  self->threshold = threshold;
  self->recived_value = 0.0f;
  self->time = initial_time;
  self->time_increment = time_increment;

  self->x = x;
  self->y = y;
  self->z = z;
  self->e = e;
  self->S = S;
  self->m = m;

  return self;
}

float HindmarshRose_calculate(HindmarshRose *self) {
  float aux_x, aux_y, aux_z;

  aux_x = self->x + self->time_increment *
                        (self->y + 3 * self->x * self->x -
                         self->x * self->x * self->x - self->z + self->e);
  aux_y =
      self->y + self->time_increment * (1 - 5 * self->x * self->x - self->y);
  aux_z = self->z + self->time_increment * self->m *
                        (-self->z + self->S * (self->x + 1.6));

  self->x = aux_x;
  self->y = aux_y;
  self->z = aux_z;

  self->time = self->time + self->time_increment;

  return self->x;
}
void HindmarshRose_free(HindmarshRose *self) { free(self); }
