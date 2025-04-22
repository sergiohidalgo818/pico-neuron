/**
 * @file HindmarshRose.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header File for the Hindmarsh Rose HindmarshRose
 * @version 0.1
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 */
#ifndef HINDMARSH_ROSE_H
#define HINDMARSH_ROSE_H
#include "Model.hpp"
#define HINDMARSH_ROSE_NPARAMS 6
/**
 * @class HindmarshRose
 * @brief This class implements the Hindmarsh-Rose model.
 *
 *
 */
class HindmarshRose : public Model {

public:
  float x;
  float y;
  float z;
  float e;
  float S;
  float m;

public:
  /**
   * @brief This function initialices the Hindmarsh-Rose model.
   * @param synaptic Indicates if the Hindmarsh-Rose model will respond at the
   * inputs.
   * @param initial_values The initial values for the model.
   * @param initial_time The initial time for the model.
   * @param time_increment The time increment for the model.
   *
   * @return Returns the Hindmarsh-Rose model initialized.
   */
  HindmarshRose(bool synaptic, std::vector<float> initial_values,
                float initial_time, float time_increment);

  /**
   * @brief This function initialices the Hindmarsh-Rose model.
   * @param synaptic Indicates if the Hindmarsh-Rose model will respond at the
   * inputs.
   * @param threshold The threshold for the neuron.
   * @param initial_values The initial values for the model.
   * @param initial_time The initial time for the model.
   * @param time_increment The time increment for the model.
   *
   * @return Returns the Hindmarsh-Rose model initialized.
   */
  HindmarshRose(bool synaptic, float threshold,
                std::vector<float> initial_values, float initial_time,
                float time_increment);
  /**
   * @brief This function calculates the next time on the Hindmarsh-Rose model.
   *
   * @return Returns the calculated value.
   */
  virtual void calculate();

  /**
   * @brief This function frees the Hindmarsh-Rose model.
   *
   */

  void free();
};

#endif /* HINDMARSH_ROSE_H */
