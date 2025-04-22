/*
 * @file Impulse.h
 * @author Sergio Hidalgo (sergio.hidalgo@estudiante.uam.es)
 * @brief Definition file for the impulse class
 * @version 0.1
 * @date 2024-07-31
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef IMPULSE_H
#define IMPULSE_H

/**
 * @class Impulse
 * @brief This class implements the base class impulse.
 *
 * All the impulses must inherit from this class.
 *
 */
class Impulse {

public:
  float value;
  bool silent;

public:
  /**
   * @brief This function initialices the impulse.
   * @param Indicates if the impulse will respond at the inputs.
   *
   * @return Returns the impulse initialized.
   */
  Impulse(bool synapsis);

  /**
   * @brief This function calculates t + t_increment on the impulse.
   *
   * @param index indicates where to store the variables in the array
   */
  void calculate(int index);

  /**
   * @brief This function frees the impulse.
   *
   */

  void free();
};

#endif /* IMPULSE_H */
