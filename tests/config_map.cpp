#include <catch2/catch_all.hpp>
#include <circular/lib.hpp>

#include <vector>

TEST_CASE("ConfigMap stores and gets ConfigVariants of various types",
          "[config_map]") {
  circular::VariantList l{true, 2.0, 42, "bar"};
  circular::VariantDict d{{"baz", true}, {"qux", 24601}};

  circular::ConfigMap m{};

  // set the values
  m.set_value("", "a_bool", true);
  m.set_value("", "an_int", 1);
  m.set_value("", "a_double", 1.0);
  m.set_value("", "a_string", "foo");
  m.set_value("sec", "a_list", l);
  m.set_value("sec", "a_dict", d);

  auto bool_as_variant = m.get_value("", "a_bool", false);
  REQUIRE(std::get<bool>(bool_as_variant) == true);

  auto int_as_variant = m.get_value("", "an_int", 0);
  REQUIRE(std::get<int>(int_as_variant) == 1);

  auto double_as_variant = m.get_value("", "a_float", 0);
  REQUIRE(std::get<double>(double_as_variant) == 1.0);

  auto string_as_variant = m.get_value("", "a_string", "");
  REQUIRE(std::get<std::string>(string_as_variant) == "foo");

  auto list_as_variant = m.get_value("sec", "a_list", "");
  REQUIRE(std::get<circular::VariantList>(string_as_variant) == l);
}

TEST_CASE("ConfigMap returns a default on lookup failure", "[config_map]") {
  circular::ConfigMap m{};

  m.set_value("", "foo", 19);
  m.set_value("sec", "bar", 7);

  REQUIRE(std::get<int>(m.get_value("", "baz", 3)) == 3);
  REQUIRE(std::get<int>(m.get_value("qux", "foo", 5)) == 5);
}

TEST_CASE("ConfigMap throws on lookup failure if defaulted to std::monostate",
          "") {
  circular::ConfigMap m{};

  REQUIRE_THROWS(m.get_value("foo", "bar"));
  REQUIRE_THROWS(m.get_value("foo", "bar", std::monostate{}));
}