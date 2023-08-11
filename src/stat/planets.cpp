#include "planets.hpp"

#include <cmath>

#include "trick_math.hpp"

using namespace circular;

double circular::astro::planetSurfaceArea(double radius) {
  return 4.0 * M_PI * _pow2(radius);
}

double circular::astro::planetMass(double density, double radius) {
  return (4.0 / 3.0) * M_PI * density * _pow3(radius);
}

double circular::astro::planetSurfaceGravity(double density, double radius) {
  return param::NewtonConst * planetMass(density, radius) / _pow2(radius);
}

double circular::astro::orbitalPeriod(double semiMajorAxis,
                                      double primaryMass) {
  return 2.0 * M_PI *
         std::sqrt(_pow3(semiMajorAxis) / (param::NewtonConst * primaryMass));
}

double circular::astro::sunMass(double sunSize) {
  return std::pow(sunSize, 1.25) * param::MassSun;
}

double circular::astro::sunEmission(double sunTemp) {
  return param::StefanBoltzmannConst * _pow4(sunTemp);
}

double circular::astro::sunConstant(double sunTemp, double sunSize,
                                    double distance) {
  auto area_ratio = _pow2(sunSize * param::RadiusSun) / _pow2(distance);
  return sunEmission(sunTemp) * area_ratio;
}

double circular::astro::planetaryBalanceTemperature(double sunConstant,
                                                    double bondAlbedo,
                                                    double emissivity) {
  auto balance_emission = (1.0 - bondAlbedo) * sunConstant /
                          (4.0 * param::StefanBoltzmannConst * emissivity);
  return std::pow(balance_emission, 0.25);
}

double circular::astro::sunApparentSize(double sunSize, double distance) {
  return 2.0 * std::asin(sunSize * param::RadiusSun / distance);
}
