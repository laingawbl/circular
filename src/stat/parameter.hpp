/**
 * @file parameter.hpp
 * @author Alex Laing (livingearthcompany@gmail.com)
 * @brief Data and helper types for World.
 */

#pragma once

#include <array>
#include <cmath>
#include <ostream>
#include <string>

namespace circular {
namespace param {

/**
 * @brief A Harmonic represents a cyclical or sinusoidal value, which oscillates
 * about a central value over time.
 */
struct Harmonic {
  Harmonic() = delete;
  Harmonic(double centre, double amplitude, double period, double phase = 0.0)
      : _centre{centre}, _amplitude{amplitude}, _period{period}, _phase{phase} {
  }

  inline static Harmonic fromMinMax(double min, double max, double period,
                                    double phase = 0.0) {
    return Harmonic(0.5 * (min + max), max - min, period, phase);
  }
  inline static Harmonic fromCentre(double centre, double amplitude,
                                    double period, double phase = 0.0) {
    return Harmonic(centre, amplitude, period, phase);
  }

  inline double at(double t) const {
    return _centre + _amplitude * std::sin((t * 2.0 * M_PI / _period) + _phase);
  }

  double _centre;
  double _amplitude;
  double _period;
  double _phase;
};

/**
 * @brief A linearly-interpolated 1-dimensional lookup table (LUT).
 *
 * @tparam N the number of samples in the LUT. e.g.: Lut1D<3> samples from a
 * std::array<double, 3>.
 */
template <int N> struct Lut1D {
  Lut1D() = delete;
  Lut1D(double a, double b) : _from{a}, _to{b}, _spread{b - a} {}

  double _from;
  double _to;
  double _spread;

  std::array<double, N> _samples{};

  inline double at(double x) const {
    auto xnorm = std::clamp((x - _from) / _spread, 0.0, 1.0);
    int A = std::floor(xnorm * (N - 1));
    int B = (A + 1) % N;
    double t = xnorm * static_cast<double>(N - 1) - static_cast<double>(A);
    return std::lerp(_samples[A], _samples[B], t);
  }
};

/**
 * @brief A linearly-interpolated 2-dimensional lookup table (LUT).
 *
 * @tparam N The number of samples in the LUT's first index.
 * @tparam M The number of samples in the LUT's second index.
 */
template <int N, int M> struct Lut2D {
  Lut2D() = delete;
  Lut2D(double a, double b, double x, double y)
      : _a{a}, _b{b}, _spread_ab{b - a}, _x{x}, _y{y}, _spread_xy{y - x} {}

  double _a;
  double _b;
  double _spread_ab;
  double _x;
  double _y;
  double _spread_xy;

  std::array<std::array<double, M>, N> _samples{};

  inline double at(double u, double v) const { return 0.0; }
};

/**
 * @brief A named value which you CAN mutate, but which you really shouldn't, or
 * something... I'm not sure this is a good or intentful class or not and may
 * delete it...
 *
 * @tparam T the underlying type of the parameter.
 */
template <typename T> class Parameter {
public:
  Parameter(T val = T{}, std::string_view key = "")
      : _value{val}, _key{std::string{key}} {}
  std::string _key;

  T get() const { return _value; }
  T operator()() const { return _value; }
  void set(const T &newVal) { _value = newVal; }

private:
  T _value;
};

} // namespace param
} // namespace circular