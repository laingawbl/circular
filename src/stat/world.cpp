#include "world.hpp"

#include "planets.hpp"

using namespace circular;

template <typename T>
void lookupHelper(const ConfigMap &map, param::Parameter<T> &parm,
                  const std::string &section) {
  if (map.has_section_key(section, parm._key)) {
    parm.set(std::get<T>(map.get_value(section, parm._key)));
  }
}

circular::World::World(const ConfigMap &options) {
  const std::string bodySection = "body";

  lookupHelper(options, orbitRadius, bodySection);
  lookupHelper(options, sunSize, bodySection);
  lookupHelper(options, sunTemp, bodySection);

  auto eccMin = std::get<double>(options.get_value(bodySection, "ecc_min", 0.));
  auto eccMax = std::get<double>(options.get_value(bodySection, "ecc_max", 0.));
  auto eccPeriod = std::get<double>(
      options.get_value(bodySection, "ecc_period", eccentricity()._period));
  auto eccPhase = std::get<double>(
      options.get_value(bodySection, "ecc_phase", eccentricity()._phase));
  eccentricity.set(
      param::Harmonic::fromMinMax(eccMin, eccMax, eccPeriod, eccPhase));

  lookupHelper(options, bodyPeriod, bodySection);
  lookupHelper(options, bodyRadius, bodySection);
  lookupHelper(options, bodyDensity, bodySection);

  calcBodyParams();
}

void circular::World::calcBodyParams() {
  bodySurfaceArea = astro::planetSurfaceArea(bodyRadius());
  bodyMass = astro::planetMass(bodyDensity(), bodyRadius());
  bodyGravity = astro::planetSurfaceGravity(bodyDensity(), bodyRadius());
  sunConstant = astro::sunConstant(sunTemp(), sunSize(), orbitRadius());
  planetaryBalanceTemperature = astro::planetaryBalanceTemperature(
      sunConstant, should_be_defines::BondAlbedo,
      should_be_defines::Emissivity);
}
