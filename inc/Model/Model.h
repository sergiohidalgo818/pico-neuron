/**
 * @file Model.h
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Definition file for the model struct
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef MODEL_H
#define MODEL_H

#include "types.h"

typedef;
/**
 * @struct Model
 * @brief This struct implements the base model.
 *
 * All the models must contain this struct as their first member.
 *
 */
typedef float (*CalculateFunc)(void *context);
typedef struct Model {
  bool synaptic;
  float threshold;
  float output_value;
  float recived_value;
  float time;
  float time_increment;
  CalculateFunc calculate;
  void *inherited_model;
} Model;

/**
 * @brief This function initializes the model.
 * @param synaptic Indicates if the model will respond at the inputs.
 * @param initial_time The initial time for the model.
 * @param time_increment The time increment for the model.
 *
 * @return Returns a pointer to the initialized model.
 */
Model *Model_create(bool synaptic, float initial_time, float time_increment);

/**
 * @brief This function initializes the model.
 * @param synaptic Indicates if the model will respond at the inputs.
 * @param threshold The threshold for the neuron.
 * @param initial_time The initial time for the model.
 * @param time_increment The time increment for the model.
 *
 * @return Returns a pointer to the initialized model.
 */
Model *Model_createWithThreshold(bool synaptic, float threshold,
                                 float initial_time, float time_increment);

/**
 * @brief Sends a value to the model.
 * @param self Pointer to the Model object
 * @param recived_value The value sent
 */
void Model_interact(Model *self, float recived_value);

/**
 * @brief This function calculates the next time on the model.
 * @param self Pointer to the Model object
 * @return Returns the calculated value.
 */
float Model_calculate(Model *self);

/**
 * @brief This function frees the model.
 * @param self Pointer to the Model object
 */
void Model_free(Model *self);

#endif /* MODEL_H */
