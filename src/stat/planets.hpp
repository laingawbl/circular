#pragma once

#include "constants.hpp"
#include "parameter.hpp"

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

/// @brief The true anomaly of a body, in an orbit of eccentricity Eccentricity,
/// at fractional time of the orbit [0..1) timeInYear. The periapsis is assumed
/// to be at 0.0, but can be set via [0..1] timeOfPeriapsis.
/// @param eccentricity
/// @param year
/// @param timeInYear
/// @return in radians.
double calcTrueAnomaly(double eccentricity, double timeInYear,
                       double timeOfPeriapsis = 0.0);

/// @brief Calculate the solar declination on a planet with tilt AxialTilt and
/// orbital true anomaly TrueAnomaly, at a fractional time in the year [0..1]
/// TimeInYear. This value should be zero at the equinoxes, and a maximal or
/// minimal value at either solstice.
/// @param trueAnomaly
/// @param timeInYear
/// @return in radians.
double calcDeclination(double axialTilt, double trueAnomaly, double timeInYear);

/// @brief Calculate the average exposure per rotation, of a location on a
/// rotating planet, at latitude Latitude, to a sun at declination Declination.
/// Keep in mind that this value is decreasingly meaningful as the length of a
/// planetary rotation (i.e. a day) approaches the length of a planetary orbit
/// (i.e. a year), or matches it, as on tidally-locked bodies.
/// @param latitude
/// @param declination
/// @return dimensionless ratio in [0..1], corresponding to the fractional
/// brightness of a _constant, direct illumination_ that would match the daily
/// average energy from the moving sun at that latitude.
double calcDailySunExposure(double latitude, double declination);

} // namespace astro
} // namespace circular
