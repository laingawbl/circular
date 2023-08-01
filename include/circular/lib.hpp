#pragma once

#include <tuple>
#include <vector>

/// \brief Accumulate a vector to produce the mean and the first moment of the
/// distribution.
///
/// This computes the mean and the first moment of a vector of double values.
///

namespace circular {
std::tuple<double, double>
accumulate_vector(const std::vector<double> &values ///< The vector of values
);
}