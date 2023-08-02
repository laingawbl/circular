#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <circular/lib.hpp>

TEST_CASE("Quick check", "[main]") {
  std::vector<double> values{1, 2., 3.};
  auto [mean, var] = circular::accumulate_vector(values);

  REQUIRE(mean == 2.0);
  REQUIRE_THAT(var, Catch::Matchers::WithinAbs(0.666666, 1e-6));
}
