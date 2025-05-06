/**
 * @file HindmarshRose.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header File for the Hindmarsh Rose HindmarshRose
 * @version 0.1
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 */
#ifndef HINDMARSH_ROSE_H
#define HINDMARSH_ROSE_H

#include "Model.h"
#include "types.h"
#define HINDMARSH_ROSE_NPARAMS 6

/**
 * @struct HindmarshRose
 * @brief This struct implements the Hindmarsh-Rose model.
 *
 */
typedef struct HindmarshRose {
  bool synaptic;
  float threshold;
  float recived_value;
  float time;
  float time_increment;
  float x;
  float y;
  float z;
  float e;
  float S;
  float m;
} HindmarshRose;

/**
 * @brief This function initializes the Hindmarsh-Rose model.
 * @param synaptic Indicates if the Hindmarsh-Rose model will respond at the
 * inputs.
 * @param initial_time The initial time for the model.
 * @param time_increment The time increment for the model.
 * @param x The x value for the model.
 * @param y The y value for the model.
 * @param z The z value for the model.
 * @param e The e value for the model.
 * @param S The S value for the model.
 * @param m The m value for the model.
 *
 * @return Returns a pointer to the Hindmarsh-Rose model initialized.
 */
HindmarshRose *HindmarshRose_init(bool synaptic, float initial_time,
                                  float time_increment, float x, float y,
                                  float z, float e, float S, float m);

/**
 * @brief This function initializes the Hindmarsh-Rose model.
 * @param synaptic Indicates if the Hindmarsh-Rose model will respond at the
 * inputs.
 * @param threshold The threshold for the neuron.
 * @param initial_time The initial time for the model.
 * @param time_increment The time increment for the model.
 * @param x The x value for the model.
 * @param y The y value for the model.
 * @param z The z value for the model.
 * @param e The e value for the model.
 * @param S The S value for the model.
 * @param m The m value for the model.
 *
 * @return Returns a pointer to the Hindmarsh-Rose model initialized.
 */
HindmarshRose *HindmarshRose_initWithThreshold(bool synaptic, float threshold,
                                               float initial_time,
                                               float time_increment, float x,
                                               float y, float z, float e,
                                               float S, float m);

/**
 * @brief This function calculates the next time on the Hindmarsh-Rose model.
 * @param self Pointer to the HindmarshRose object
 * @return Returns the calculated value.
 */
float HindmarshRose_calculate(HindmarshRose *self);

/**
 * @brief This function frees the Hindmarsh-Rose model.
 * @param self Pointer to the HindmarshRose object
 */
void HindmarshRose_free(HindmarshRose *self);

#endif /* HINDMARSH_ROSE_H */
