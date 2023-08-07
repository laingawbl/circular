#include "config_map.hpp"

using namespace circular;

void circular::ConfigMap::clear() {}

void circular::ConfigMap::erase_section(std::string section) {}

void circular::ConfigMap::erase_section_key(std::string section,
                                            std::string key) {}

std::vector<std::string>
circular::ConfigMap::get_section_keys(std::string section) const {
  return std::vector<std::string>();
}

std::vector<std::string> circular::ConfigMap::get_sections() const {
  return std::vector<std::string>();
}

ConfigVariant circular::ConfigMap::get_value(std::string section,
                                             std::string key,
                                             ConfigVariant default_value) {
  return ConfigVariant();
}

void circular::ConfigMap::set_value(std::string section, std::string key,
                                    ConfigVariant value) {}
