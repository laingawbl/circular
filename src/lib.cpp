#include "circular/lib.hpp"

#include <numeric>

namespace circular {
std::tuple<double, double>
accumulate_vector(const std::vector<double> &values) {
  auto len = values.size();
  double mean = std::reduce(values.begin(), values.end()) / len;
  auto variance = std::accumulate(values.begin(), values.end(), 0.0,
                                  [mean](const double &a, const double &b) {
                                    auto diff = mean - b;
                                    return a + (diff * diff);
                                  });
  return {mean, variance / len};
}
} // namespace circular