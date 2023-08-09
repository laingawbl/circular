#include <catch2/catch_all.hpp>
#include <circular/config_map.hpp>

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

  auto bool_as_variant = m.get_value("", "a_bool", circular::ConfigVariant{});
  REQUIRE(std::get<bool>(bool_as_variant) == true);

  auto int_as_variant = m.get_value("", "an_int", circular::ConfigVariant{});
  REQUIRE(std::get<int>(int_as_variant) == 1);

  auto double_as_variant =
      m.get_value("", "a_double", circular::ConfigVariant{});
  REQUIRE(std::get<double>(double_as_variant) == 1.0);

  auto string_as_variant =
      m.get_value("", "a_string", circular::ConfigVariant{});
  REQUIRE(std::get<std::string>(string_as_variant) == "foo");

  auto list_as_variant =
      m.get_value("sec", "a_list", circular::ConfigVariant{});
  REQUIRE(std::get<circular::VariantList>(list_as_variant) == l);

  auto dict_as_variant =
      m.get_value("sec", "a_dict", circular::ConfigVariant{});
  REQUIRE(std::get<circular::VariantDict>(dict_as_variant) == d);
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

TEST_CASE("ConfigMap deletes keys", "[config_map]") {
  circular::ConfigMap m{};

  m.set_value("", "foo", 19);
  m.set_value("sec", "bar", 7);
  m.erase_section_key("sec", "bar");

  REQUIRE(m.get_section_keys("").size() == 1);
  REQUIRE(m.get_section_keys("sec").size() == 0);
}

TEST_CASE("ConfigMap can test for section and key existence", "[config_map]") {
  circular::ConfigMap m{};

  m.set_value("", "foo", 19);
  m.set_value("sec", "bar", 7);

  REQUIRE(m.has_section("sec") == true);
  REQUIRE(m.has_section("baz") == false);

  REQUIRE(m.has_section_key("sec", "bar") == true);
  REQUIRE(m.has_section_key("sec", "qux") == false);
  REQUIRE(m.has_section_key("ick", "foo") == false);
}

TEST_CASE("ConfigMap parses a file with valid TOML subset", "[config_map]") {
  auto m = circular::ConfigMap::parse_from_file("tests/fixtures/good.toml");

  REQUIRE(std::get<int>(m.get_value("", "no_section")) == 2);
  REQUIRE(std::get<int>(m.get_value("foo", "bar")) == 1);
  REQUIRE(std::get<double>(m.get_value("bar", "quoted")) ==
          Catch::Approx(1.61828));

  circular::VariantList l{1.0, true, "jimmy"};
  REQUIRE(std::get<circular::VariantList>(m.get_value("foo", "mixedList")) ==
          l);
}

TEST_CASE("ConfigMap throws on invalid files", "[config_map]") {
  REQUIRE_THROWS(
      circular::ConfigMap::parse_from_file("tests/fixtures/bad.toml"));
}