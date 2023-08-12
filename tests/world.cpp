#include <catch2/catch_all.hpp>

#include "../src/stat/parameter.hpp"
#include "../src/stat/planets.hpp"
#include "../src/stat/world.hpp"

using namespace circular;

TEST_CASE("Lut1D works", "[parameter]") {
  param::Lut1D<3> lut(0.0, 2.0);
  lut._samples[1] = 1.0;
  lut._samples[2] = 2.0;

  REQUIRE(lut.at(-1.0) == Catch::Approx(0.0));
  REQUIRE(lut.at(0.5) == Catch::Approx(0.5));
  REQUIRE(lut.at(2.0) == Catch::Approx(2.0));
  REQUIRE(lut.at(2.5) == Catch::Approx(2.0));
}

TEST_CASE("Lut1D works with reversed bounds", "[parameter]") {
  param::Lut1D<3> lut(2.0, 0.0);
  lut._samples[1] = 1.0;
  lut._samples[2] = 2.0;

  REQUIRE(lut.at(-1.0) == Catch::Approx(2.0));
  REQUIRE(lut.at(0.5) == Catch::Approx(1.5));
  REQUIRE(lut.at(2.0) == Catch::Approx(0.0));
  REQUIRE(lut.at(2.5) == Catch::Approx(0.0));
}

TEST_CASE("Planetary sanity check", "[parameter][.verb]") {
  auto sun_const =
      astro::sunConstant(param::TempSun, 1.0, param::AstronomicalUnit);
  auto balance_temp = astro::planetaryBalanceTemperature(sun_const, 0.29, 1.00);

  REQUIRE(sun_const == Catch::Approx(1361).epsilon(1e-3));
  REQUIRE(balance_temp == Catch::Approx(255.5).epsilon(1e-3));

  auto g_earth =
      astro::planetSurfaceGravity(param::DensityEarth, param::RadiusEarth);
  REQUIRE(g_earth == Catch::Approx(9.8203).epsilon(1e-3));
}

TEST_CASE("World sanity check", "[parameter][.verb]") {
  auto w = World(ConfigMap{});

  REQUIRE(w.getSunConstant() == Catch::Approx(1361).epsilon(1e-3));
  REQUIRE(w.getPlanetaryBalanceTemperature() ==
          Catch::Approx(258).epsilon(1e-3));
  REQUIRE(w.getBodyGravity() == Catch::Approx(9.8203).epsilon(1e-3));
}

TEST_CASE("World loads Venus parameters, and updates them on setting a primary",
          "[parameter][.verb]") {
  auto venus_def = ConfigMap::parse_from_file("tests/fixtures/venus.toml");
  auto w = World(venus_def);

  REQUIRE(w.getBodyGravity() == Catch::Approx(8.87).epsilon(1e-3));
  REQUIRE(w.getPlanetaryBalanceTemperature() ==
          Catch::Approx(303).epsilon(1e-3));

  auto oldBodyGravity = w.getBodyGravity();
  w.setBodyDensity(w.getBodyDensity() + 1.0);
  REQUIRE(w.getBodyGravity() > oldBodyGravity);
}