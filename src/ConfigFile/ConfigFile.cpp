
#include "ConfigFile/ConfigFile.hpp"
#include <fstream>
#include <regex>
#include <sstream>

bool ConfigFile::is_number(const std::string &str) {
  std::regex pattern("^[+-]?\\d*(\\.\\d+)?([eE][+-]?\\d+)?$");
  return std::regex_match(str, pattern);
}

std::map<std::string, std::string>
ConfigFile::read_config(const std::string &filename) {
  std::map<std::string, std::string> config;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    // Trim leading spaces
    line.erase(0, line.find_first_not_of(" \t"));

    // Skip empty lines and comment lines
    if (line.empty() || line[0] == '#' || line[0] == ';')
      continue;

    // Strip inline comments
    size_t comment_pos = line.find_first_of("#;");
    if (comment_pos != std::string::npos) {
      line = line.substr(0, comment_pos);
    }

    // Parse key=value
    std::istringstream iss(line);
    std::string key, value;
    if (std::getline(iss, key, '=') && std::getline(iss, value)) {
      // Trim whitespace
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      config[key] = value;
    }
  }

  return config;
}

std::vector<float> ConfigFile::string_to_vector(const std::string &str) {
  std::vector<float> result;
  std::stringstream ss(str);
  std::string temp;

  while (std::getline(ss, temp, ',')) {
    temp.erase(0, temp.find_first_not_of(" \t"));
    temp.erase(temp.find_last_not_of(" \t") + 1);
    if (ConfigFile::is_number(temp)) {

      result.push_back(std::stof(temp)); // std::stof to convert string to float
    } else {
      result.push_back(1.0);
    }
  }

  return result;
}
