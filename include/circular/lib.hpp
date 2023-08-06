#pragma once

#include <tuple>
#include <vector>

#include "tasker.hpp"

/// \brief Accumulate a vector to produce the mean and the variance of the
/// distribution.
///
/// This computes the mean and the variance of a vector of double values.
///

namespace circular {
std::tuple<double, double>
accumulate_vector(const std::vector<double> &values ///< The vector of values
);
}