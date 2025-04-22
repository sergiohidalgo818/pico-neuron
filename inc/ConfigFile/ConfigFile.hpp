/**
 * @file ConfigFile.hpp
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief File that tools for reading the config.
 * @version 0.1
 * @date 2025-04-21
 *
 * @copyright Copyright (c) 2025
 */
#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H
#include <map>
#include <string>
#include <vector>

/**
 * @class ConfigFile
 * @brief Configuration for the program
 *
 * Parses the file with the values needed to run the program.
 *
 */
class ConfigFile {
public:
  static bool is_number(const std::string &str);
  static std::map<std::string, std::string>
  read_config(const std::string &filename);
  static std::vector<float> string_to_vector(const std::string &str);
};
#endif /* CONFIG_FILE_H */
