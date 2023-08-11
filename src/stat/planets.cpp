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

double circular::astro::calcTrueAnomaly(double eccentricity, double timeInYear,
                                        double timeOfPeriapsis) {
  /// Impl: Copied from pan-gaia. This is an approximation via a Taylor series
  /// expansion. Is it necessary now?
  const double M = 2.0 * M_PI * timeInYear; // Mean anomaly
  const auto &e = eccentricity;
  return M + 2 * e * std::sin(M) + (5. / 4.) * e * e * std::sin(2 * M);
}

double circular::astro::calcDeclination(double axialTilt, double trueAnomaly,
                                        double timeInYear) {
  return axialTilt * std::sin(trueAnomaly);
}

double circular::astro::calcDailySunExposure(double latitude,
                                             double declination) {
  // Impl: Copied from pan-gaia.
  const auto determinant = -std::tan(latitude) * std::tan(declination);
  double H0 = 0.0; // sunrise hour

  if (determinant <= -1.0) { // check for no sunrise
    H0 = M_PI;
  } else if (determinant < 1.0) {
    H0 = std::acos(determinant);
  }

  return std::max(0.0, M_1_PI * H0 * std::sin(H0) * std::sin(latitude) *
                           std::sin(declination) * std::cos(latitude) *
                           std::cos(declination));
}
