#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace circular {

using PodVariant = std::variant<std::monostate, bool, int, double,
                                std::string>; // no containers

using VariantList = std::vector<PodVariant>;
using VariantDict = std::unordered_map<std::string, PodVariant>;

using ConfigVariant =
    std::variant<std::monostate, bool, int, double, std::string, VariantList,
                 VariantDict>; // has containers

/**
 * @brief A two-level unordered_map from string sections/keys to variant values.
 *
 * ConfigMap is an STL-based analogue to godot::ConfigFile, with three
 * differences:
 * 1. no methods to read/write/parse/stringify; and
 * 2. values are restricted to {BOOL, INT, DOUBLE, STRING, ARRAY, DICT}, and
 * 3. The ARRAY and DICT therein are limited to non-container types. Sorry.
 * It stores key-value pairs, with std::string keys and std::variant values.
 * These pairs are further collected into sections, identified by std::string
 * section keys.
 *
 * The consumer should handle conversion to and from godot::ConfigFile,
 * including the rules for transforming keys/sections <->
 * std::string and values <-> ConfigVariant.
 */
class ConfigMap {
  using _config_section_t = std::unordered_map<std::string, ConfigVariant>;
  using _config_map_repr_t = std::unordered_map<std::string, _config_section_t>;

public:
  ConfigMap() = default;
  ~ConfigMap() = default;

  /// @brief erase all sections and keys, making the ConfigMap empty.
  void clear();

  /// @brief erase a single section and all its key-value pairs.
  /// @param section The section to be erased.
  ///
  /// Throws std::out_of_range if section does not exist.
  void erase_section(const std::string &section);

  /// @brief erase a key-value pair.
  /// @param section The section of the key to be erased.
  /// @param key The key whose key-value pair is to be erased.
  ///
  /// Throws std::out_of_range if either section or key do not exist.
  void erase_section_key(const std::string &section, const std::string &key);

  /// @brief list the keys present in a section.
  /// @param section The section for which a list of keys is desired.
  /// @return A vector of keys in that section (in no particular order).
  std::vector<std::string> get_section_keys(const std::string &section) const;

  /// @brief List the sections present in the ConfigMap.
  /// @return A vector of sections in the ConfigMap (in no particular order).
  std::vector<std::string> get_sections() const;

  /// @brief Look up a value, and either return a default or throw if not found.
  /// @param section The section of the key-value pair to be looked up.
  /// @param key The key to look up.
  /// @param default_value The value to return if there is no value for
  /// section/key. If you don't want this to happen, passing ConfigVariant{}
  /// (equivalently std::monostate) will result in get_value throwing
  /// std::out_of_range instead of returning anything on lookup failure.
  /// @return The value for the section/key, or the default value on lookup
  /// failure (if default_value != std::monostate).
  ///
  /// Throws std::out_of_range on lookup failure if default_value ==
  /// std::monostate.
  ConfigVariant get_value(const std::string &section, const std::string &key,
                          ConfigVariant default_value = ConfigVariant{});

  /// @brief Insert or assign a value in the ConfigMap.
  /// @param section The section of the key-value pair to create.
  /// @param key The key whose value is to be set.
  /// @param value The value to be assigned. Passing ConfigVariant{}
  /// (equivalently std::monostate) will delete the key (i.e., null it out).
  ///
  /// If either section or key do not exist, they will be created.
  void set_value(const std::string &section, const std::string &key,
                 ConfigVariant value);

  /// @brief Test whether the ConfigMap contains a section with that name.
  /// @param section The section whose existence is in question.
  /// @return true if the ConfigMap contains a section with that name.
  bool has_section(const std::string &section) const;

  /// @brief Test whether the ConfigMap contains a section and key with that
  /// name.
  /// @param section The section of the key whose existence is in question.
  /// @param key The key whose existence is in question.
  /// @return true if the ConfigMap contains a section/key with those names.
  bool has_section_key(const std::string &section,
                       const std::string &key) const;

private:
  _config_map_repr_t _repr{};
};
} // namespace circular