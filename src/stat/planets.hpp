#pragma once

#include "constants.hpp"

namespace circular {
namespace astro {
/// @brief The area of a sphere with radius Radius.
/// @param Radius
/// @return in square meters [m^2].
double planetSurfaceArea(double radius);

/// @brief The mass of a sphere with density Density and radius Radius.
/// @param Density
/// @param Radius
/// @return in kilograms [kg].
double planetMass(double density, double radius);

/// @brief The surface gravity of a sphere with density Density and radius
/// Radius.
/// @param Density
/// @param Radius
/// @return in metres per square second [m / s^2]
double planetSurfaceGravity(double density, double radius);

/// @brief The orbital period of a body with semi-major axis SemiMajorAxis,
/// orbiting a (much more massive) primary body of mass PrimaryMass.
/// @param SemiMajorAxis
/// @param PrimaryMass
/// @return in seconds [s].
double orbitalPeriod(double semiMajorAxis, double primaryMass);

/// @brief The mass of a main-branch star which is SunSize times our Sun's
/// radius. For Sun-like stars, the relationship R = M^{0.8} holds.
/// @param SunSize
/// @return in kilograms [kg].
double sunMass(double sunSize);

/// @brief The outgoing energy per unit area of a blackbody at temperature
/// SunTemp.
/// @param SunTemp
/// @return in Watts per square metre [W / m^2].
double sunEmission(double sunTemp);

/// @brief The incoming energy per unit area, at a distance Distance, from a
/// star of temperature SunTemp and radius SunSize (in radii of our Sun).
/// @param SunTemp
/// @param SunSize
/// @param SemiMajorAxis
/// @return in Watts per square metre [W / m^2].
double sunConstant(double sunTemp, double sunSize, double distance);

/// @brief The equilibrium temperature for a rotating body with Bond albedo
/// BondAlbedo, experiencing an incoming energy flux of SunConstant.
/// @param SunConstant
/// @param BondAlbedo
/// @param emissivity
/// @return in Kelvin [K].
double planetaryBalanceTemperature(double sunConstant, double bondAlbedo,
                                   double emissivity = 0.95);

/// @brief The apparent angular size for a body of size SunSize (in radii of our
/// Sun), seen at a distance Distance.
/// @param SunSize
/// @param Distance
/// @return in radians.
double sunApparentSize(double sunSize, double distance);
} // namespace astro
} // namespace circular