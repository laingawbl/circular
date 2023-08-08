#include "config_map.hpp"

#include <stdexcept>

using namespace circular;

void circular::ConfigMap::clear() { _repr.clear(); }

void circular::ConfigMap::erase_section(const std::string &section) {
  auto f = _repr.find(section);
  if (f == _repr.end()) {
    throw std::out_of_range{
        "erase_section: trying to erase nonexistent section"};
  }
  _repr.erase(f);
}

void circular::ConfigMap::erase_section_key(const std::string &section,
                                            const std::string &key) {
  auto &d = _repr.at(section);
  auto k = d.find(key);
  if (k == d.end()) {
    throw std::invalid_argument{
        "erase_section_key: trying to erase nonexistent key"};
  }
  d.erase(k);
}

std::vector<std::string>
circular::ConfigMap::get_section_keys(const std::string &section) const {
  auto d = _repr.at(section);

  std::vector<std::string> keys{};
  keys.reserve(d.size());
  for (const auto kv : d) {
    keys.push_back(kv.first);
  }

  return keys;
}

std::vector<std::string> circular::ConfigMap::get_sections() const {
  std::vector<std::string> sections{};
  sections.reserve(_repr.size());
  for (const auto kv : _repr) {
    sections.push_back(kv.first);
  }

  return sections;
}

ConfigVariant circular::ConfigMap::get_value(const std::string &section,
                                             const std::string &key,
                                             ConfigVariant default_value) {
  auto finds = _repr.find(section);
  if (finds == _repr.end()) {
    if (default_value == ConfigVariant{}) {
      throw std::out_of_range{
          "get_value: section not found, and default_value == std::monostate"};
    }
    return default_value;
  }

  auto &d = finds->second;
  auto findk = d.find(key);
  if (findk == d.end()) {
    if (default_value == ConfigVariant{}) {
      throw std::out_of_range{
          "get_value: key not found, and default_value == std::monostate"};
    }
    return default_value;
  }

  return findk->second;
}

void circular::ConfigMap::set_value(const std::string &section,
                                    const std::string &key,
                                    ConfigVariant value) {
  auto finds = _repr.find(section);
  if (finds == _repr.end()) {
    _config_section_t new_section_repr{{key, value}};
    _repr.emplace(std::make_pair(section, new_section_repr));
    return;
  }

  auto &d = finds->second;
  if (value == ConfigVariant{}) {
    auto findk = d.find(key);
    if (findk != d.end()) {
      d.erase(findk);
    }
  } else {
    d.insert_or_assign(key, value);
  }
}

bool circular::ConfigMap::has_section(const std::string &section) const {
  return _repr.contains(section);
}

bool circular::ConfigMap::has_section_key(const std::string &section,
                                          const std::string &key) const {
  return _repr.contains(section) && _repr.at(section).contains(key);
}
