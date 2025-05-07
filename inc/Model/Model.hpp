/**
 * @file Model.h
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Definition file for the model class
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef MODEL_HPP
#define MODEL_HPP

/**
 * @class Model
 * @brief This class implements the base class model.
 *
 * All the models must inherit from this class.
 *
 */
class Model {

public:
  bool synaptic;
  float threshold;
  float output_value;
  float recived_value;
  float time;
  float time_increment;

public:
  /**
   * @brief This function initialices the model.
   * @param synaptic Indicates if the model will respond at the inputs.
   * @param initial_values The initial values for the model.
   * @param initial_time The initial time for the model.
   * @param time_increment The time increment for the model.
   *
   * @return Returns the model initialized.
   */
  Model(bool synaptic, float initial_time, float time_increment);

  /**
   * @brief This function initialices the model.
   * @param synaptic Indicates if the model will respond at the inputs.
   * @param threshold The threshold for the neuron.
   * @param initial_values The initial values for the model.
   * @param initial_time The initial time for the model.
   * @param time_increment The time increment for the model.
   *
   * @return Returns the model initialized.
   */
  Model(bool synaptic, float threshold, float initial_time,
        float time_increment);

  /**
   * @brief Sends a value to the model.
   *
   * @param recived_value The value sended
   */
  void interact(float recived_value);

  /**
   * @brief This function calculates the next time on the model.
   *
   * @return Returns the calculated value.
   */
  virtual float calculate() { return 0.0; }

  /**
   * @brief This function frees the model.
   *
   */

  void free();
};

#endif /* MODEL_HPP */
