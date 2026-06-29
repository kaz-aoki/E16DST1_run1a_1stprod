#ifndef E16_OPTIONS_H
#define E16_OPTIONS_H

#include <cstdlib>
#include <optional>
#include <string>

class E16_OPTIONS
{
public:
    static E16_OPTIONS& instance() {
      static E16_OPTIONS instance;
      return instance;
    }

    // prohibit copy and move
    E16_OPTIONS(const E16_OPTIONS&) = delete;
    E16_OPTIONS& operator=(const E16_OPTIONS&) = delete;
    E16_OPTIONS(E16_OPTIONS&&) = delete;
    E16_OPTIONS& operator=(E16_OPTIONS&&) = delete;

  //const std::string& dataDirectory() const {
  //return data_directory_;
  //}

    void reload() {
      loadFromEnvironment();
    }

    bool FLAG_GTR_ONLY_TRACKING() const { return FLAG_GTR_ONLY_TRACKING_; }
    
private:
    E16_OPTIONS() {
      loadFromEnvironment();
    }
    ~E16_OPTIONS() = default;

    void loadFromEnvironment() {
      FLAG_GTR_ONLY_TRACKING_ = environmentVariableExists("E16_GTR_ONLY_TRACKING");
      //data_directory_ = getEnvironmentVariable("E16_DATA_DIR").value_or("./data");
    }

    static bool environmentVariableExists(const char* name) {
        return std::getenv(name) != nullptr;
    }

    static std::optional<std::string>
    getEnvironmentVariable(const char* name) {
      const char* value = std::getenv(name);
      
      if (value == nullptr) {
	return std::nullopt;
      }
      return std::string(value);
    }

private:
  bool FLAG_GTR_ONLY_TRACKING_ = false;
  //std::string data_directory_ = "./data";
};

#endif  // E16_OPTIONS_H
