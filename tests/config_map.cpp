#include <catch2/catch_all.hpp>
#include <circular/lib.hpp>

#include <vector>

TEST_CASE("ConfigMap stores and gets ConfigVariants of various types",
          "[config_map]") {
  circular::VariantList l{1.0, 1};

  circular::ConfigMap m{};
  m.set_value("", "a_bool", true);
  m.set_value("", "an_int", 1);
  m.set_value("", "a_float", 1.0);
  m.set_value("", "a_string", "foo");
  m.set_value("", "a_list", l);
}