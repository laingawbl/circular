#pragma once

#include <cmath>

namespace circular {
namespace param {
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


} // namespace param
} // namespace circular