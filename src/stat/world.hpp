#pragma once

#include <circular/config_map.hpp>
#include <string>

#include "constants.hpp"
#include "parameter.hpp"

namespace circular {
namespace should_be_defines {
const inline double KarmanConst = 0.4;            // [-]
const inline double SurfacePressure = 101.325e+3; // [Pa]
const inline double BondAlbedo = 0.3;             // [-]
const inline double Emissivity = 0.95;            // [-]
} // namespace should_be_defines

class World {
public:
  World() = delete;
  World(const ConfigMap &options);

  // Primaries
  param::Parameter<double> orbitRadius{
      param::AstronomicalUnit,
      "orbit_radius",
  };
  param::Parameter<double> sunSize{
      1.0,
      "sun_size",
  };
  param::Parameter<double> sunTemp{
      param::TempSun,
      "sun_temp",
  };
  param::Parameter<param::Harmonic> eccentricity{
      param::Harmonic::fromMinMax(0.005, 0.058, 4.13e+5, M_PI / 6.0),
      "eccentricity",
  };
  param::Parameter<double> bodyPeriod{
      param::PeriodEarth,
      "body_period",
  };
  param::Parameter<double> bodyRadius{
      param::RadiusEarth,
      "body_radius",
  };
  param::Parameter<double> bodyDensity{
      param::DensityEarth,
      "body_density",
  };

  // Derived
  double bodySurfaceArea;
  double bodyMass;
  double bodyGravity;
  double sunConstant;
  double planetaryBalanceTemperature;

private:
  void calcBodyParams();

  ConfigMap _createOptions;
};
} // namespace circular