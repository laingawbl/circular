#include <circular/config_map.hpp>
#include <stdexcept>
#include <toml++/toml.h>

#include <iostream>

using namespace circular;

ConfigMap circular::ConfigMap::parse_from_file(const std::string &file_path) {
  ConfigMap m{};

  auto pod_visitor = [](const toml::node &val) -> circular::PodVariant {
    if (val.is_boolean()) {
      return **val.as_boolean();
    }
    if (val.is_integer()) {
      return static_cast<int>(**val.as_integer());
    }
    if (val.is_floating_point()) {
      return **val.as_floating_point();
    }
    if (val.is_string()) {
      return **val.as_string();
    }
    return circular::PodVariant{};
  };

  auto visitor =
      [pod_visitor](const toml::node &node) -> circular::ConfigVariant {
    if (node.is_array()) {
      VariantList vlist{};
      for (auto &&v : *node.as_array()) {
        vlist.push_back(v.visit(pod_visitor));
      }
      return vlist;
    }
    if (node.is_table()) {
      VariantDict vdict{};
      for (auto &&[k, v] : *(node.as_table())) {
        std::string key_str{k.str()};
        vdict.emplace(key_str, v.visit(pod_visitor));
      }
      return vdict;
    }
    if (node.is_boolean()) {
      return **node.as_boolean();
    }
    if (node.is_integer()) {
      return static_cast<int>(**node.as_integer());
    }
    if (node.is_floating_point()) {
      return **node.as_floating_point();
    }
    if (node.is_string()) {
      return **node.as_string();
    }
    return circular::ConfigVariant{};
  };

  auto toml_parsed = toml::parse_file(file_path);
  for (auto &&[k, v] : toml_parsed) {
    std::string section_str{k.str()};
    if (v.is_table()) {
      for (auto &&[sk, sv] : *v.as_table()) {
        std::string key_str{sk.str()};
        auto parsed_val = sv.visit(visitor);
        m.set_value(section_str, key_str, parsed_val);
      }
    } else {
      auto parsed_val = v.visit(visitor);
      m.set_value("", section_str, parsed_val);
    }
  }
  return m;
}

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
