/**
 * @file HindmarshRose.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Header File for the Hindmarsh Rose HindmarshRose
 * @version 0.1
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 */
#ifndef HIDMARSH_ROSE_HPP
#define HIDMARSH_ROSE_HPP
#include "Model.hpp"
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

  float gsync;
  float Sfast;
  float Esyn;
  float Vfast;

public:
  /**
   * @brief This function initialices the Hindmarsh-Rose model.
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
   * @return Returns the Hindmarsh-Rose model initialized.
   */
  HindmarshRose(bool synaptic, float initial_time, float time_increment,
                float x, float y, float z, float e, float S, float m);

  /**
   * @brief This function initialices the Hindmarsh-Rose model.
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
   * @return Returns the Hindmarsh-Rose model initialized.
   */
  HindmarshRose(bool synaptic, float threshold, float initial_time,
                float time_increment, float x, float y, float z, float e,
                float S, float m);
  /**
   * @brief This function calculates the next time on the Hindmarsh-Rose model.
   *
   * @return Returns the calculated value.
   */
  virtual float calculate();

  /**
   * @brief This function frees the Hindmarsh-Rose model.
   *
   */

  void free();
};

#endif /* HIDMARSH_ROSE_HPP */
