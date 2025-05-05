/**
 * @file default.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File with the default values for the config
 * @version 0.1
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 */
#ifndef DEFAULT_H
#define DEFAULT_H

/**
 * @def DECIMAL_PRECISION
 * @brief The decimal precision of the program
 * @details Override it in the correspondent model config file
 */
#ifndef DECIMAL_PRECISION
#define DECIMAL_PRECISION 0.00001
#endif
/**
 * @def MODEL_NAME
 * @brief Indicates the name of the model to use
 * @details Override it in the correspondent model config file
 */
#ifndef MODEL_NAME
#define MODEL_NAME "hindmarsh_rose"

#endif

/**
 * @def SYNAPTIC
 * @brief Indicates if the model will recive input
 * @details Override it in the correspondent model config file
 */
#ifndef SYNAPTIC
#define SYNAPTIC false
#endif

/**
 * @def RESPONSE
 * @brief Indicates the type of response for the model,
 * only works if synaptic == true
 * @details Override it in the correspondent model config file
 */
#ifndef RESPONSE
#define RESPONSE "threshold"
#endif

/**
 * @def THRESHOLD
 * @brief Indicates the value of the threshold
 * @details Override it in the correspondent model config file
 */
#ifndef THRESHOLD
#define THRESHOLD 0.75f
#endif

/**
 * @def ORDERED_PARAMS
 * @brief Indicates the initial values of the params for the model
 * @details Override it in the correspondent model config file
 */
#ifndef ORDERED_PARAMS
#define ORDERED_PARAMS 0.2f, 0.3f, 0.4f, 0.5f
#endif

/**
 * @def TIME_INCREMENT
 * @brief Indicates the time increment between each calculation
 * @details Override it in the correspondent model config file
 */
#ifndef TIME_INCREMENT
#define TIME_INCREMENT 0.001
#endif

/**
 * @def FREQUENCY
 * @brief Indicates the frequency of the model
 * @details Override it in the correspondent model config file
 */
#ifndef FREQUENCY
#define FREQUENCY 100
#endif

#endif /* DEFAULT_H */
