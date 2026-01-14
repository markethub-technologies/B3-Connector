#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace b3::oe::common {

  /**
   * @brief Simple key=value configuration file parser
   *
   * Format:
   *   key=value
   *   # comment lines (ignored)
   *   empty lines (ignored)
   */
  class ConfigParser final {
   public:
    using ConfigMap = std::unordered_map<std::string, std::string>;

    static ConfigMap load(const std::string &filepath) {
      ConfigMap config;

      std::ifstream file(filepath);
      if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + filepath);
      }

      std::string line;
      int lineNum = 0;
      while (std::getline(file, line)) {
        ++lineNum;

        // Trim leading/trailing whitespace
        line = trim(line);

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
          continue;
        }

        // Parse key=value
        auto eqPos = line.find('=');
        if (eqPos == std::string::npos) {
          throw std::runtime_error("Invalid config line " + std::to_string(lineNum) + ": " + line);
        }

        std::string key = trim(line.substr(0, eqPos));
        std::string value = trim(line.substr(eqPos + 1));

        if (key.empty()) {
          throw std::runtime_error("Empty key on line " + std::to_string(lineNum));
        }

        config[key] = value;
      }

      return config;
    }

    static std::string get(const ConfigMap &config, const std::string &key) {
      auto it = config.find(key);
      if (it == config.end()) {
        throw std::runtime_error("Missing required config key: " + key);
      }
      return it->second;
    }

    static std::string get(const ConfigMap &config, const std::string &key,
                           const std::string &defaultValue) {
      auto it = config.find(key);
      if (it == config.end()) {
        return defaultValue;
      }
      return it->second;
    }

   private:
    static std::string trim(const std::string &str) {
      const char *whitespace = " \t\r\n";
      auto start = str.find_first_not_of(whitespace);
      if (start == std::string::npos) {
        return "";
      }
      auto end = str.find_last_not_of(whitespace);
      return str.substr(start, end - start + 1);
    }
  };

} // namespace b3::oe::common
