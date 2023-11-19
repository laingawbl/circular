#include <catch2/catch_all.hpp>
#include <circular/grid.hpp>

using namespace circular;

TEST_CASE("Grids can specialise", "[grid]") {
  Grid<grids::Regular64> g64{};
  Grid<grids::Regular96> g96{};

  REQUIRE(g64.ColumnCount(0) == 64);
  REQUIRE(g64.NextX(63, 0) == 0);

  REQUIRE(g96.ColumnCount(0) == 96);
  REQUIRE(g96.NextX(63, 0) == 64);
  REQUIRE(g96.NextX(95, 0) == 0);
}