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
#ifndef MODEL_H
#define MODEL_H

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

public:
  /**
   * @brief This function initialices the model.
   * @param Indicates if the model will respond at the inputs.
   *
   * @return Returns the model initialized.
   */
  Model(bool synaptic);

  /**
   * @brief This function calculates t + t_increment on the model.
   *
   * @param index indicates where to store the variables in the array
   */
  void calculate(int index);

  /**
   * @brief This function frees the model.
   *
   */

  void free();
};

#endif /* MODEL_H */
