/**
 * @file constants.hpp
 * @author Alex Laing (livingearthcompany@gmail.com)
 * @brief Constants with generally accepted values (e.g. the density of water),
 * which do not make sense as either simulation parameters or run-time defines.
 */

#pragma once

namespace circular {
namespace param {
const inline double SalinityBrine = 357;              // [g / kg]
const inline double CpNaCl = 8.600e+02;               // [J / kg K]
const inline double CpWater = 4.184e+03;              // [J / kg K]
const inline double CryoscopicConstWater = 1.853;     // [K / kg mol]
const inline double DensityIce = 917;                 // [kg / m^3]
const inline double DensityWaterLinTerm = 6.327e-02;  // [kg / m^3 K]
const inline double DensityWaterQuadTerm = 8.524e-03; // [kg / m^3 K^2]
const inline double DensityWaterZero = 999.853;       // [kg / m^3]
const inline double DensityEarth = 5515;              // [kg / m^3]
const inline double RadiusEarth = 6.371e+6;           // [m]
const inline double KarmanConst = 0.4; // [-] TODO: This should be a define
const inline double LHFusionWater = 3.400e+05;       // [J / kg]
const inline double LHSublimWater = 2.840e+06;       // [J / kg]
const inline double LHVaporWater = 2.500e+06;        // [J / kg]
const inline double NewtonConst = 6.674e-11;         // [m^3 / kg s^2]
const inline double StefanBoltzmannConst = 5.670e-8; // [W / m^2 K^4]
const inline double MassSun = 1.988e+30;             // [kg]
const inline double RadiusSun = 6.957e+8;            // [m]
const inline double TempSun = 5772;                  // [K]
const inline double AstronomicalUnit = 1.496e+11;    // [m]
// unit conversions
const inline double ConvKilo = 1e3;
const inline double ConvKiloSquared = ConvKilo * ConvKilo;
const inline double ConvKiloCubed = ConvKilo * ConvKiloSquared;
} // namespace param
} // namespace circular