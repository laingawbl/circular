#pragma once

namespace circular {
// Impl: avoid use of std::pow
constexpr inline double _pow2(double a) { return a * a; }
constexpr inline double _pow3(double a) { return a * a * a; }
constexpr inline double _pow4(double a) { return a * a * a * a; }
} // namespace circular