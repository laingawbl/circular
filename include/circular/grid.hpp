#pragma once

/**
 * @file grid.hpp
 * @author Alex Laing (livingearthcompany@gmail.com)
 * @brief Declaration of the abstract Grid class
 */

namespace circular {
namespace grids {
struct Regular64 {};
struct Regular96 {};
struct Reduced96 {};
} // namespace grids

/**
 * @brief The Grid class is an abstraction of a regular or reduced grid on a
 * sphere with poles and an equator. We make the following assumptions:
 * - Grid points lie on circles of constant latitude ("rows").
 * - Grid points are equally spaced around these rows. However,
 * - The spacing may not be the same between each row.
 * - Spacings are symmetrical about the equator.
 *
 *
 * Grids have three types of points (names are common, e.g. from MOM5):
 * - T-points implicitly divide the sphere into quadrilateral cells. They hold
 *  information about these cells.
 * - U-points hold information about zonal matter velocity.
 * - V-points hold information about meridional matter velocity.
 *
 * The cells themselves may have non-obvious neighbours. Fields existing on
 * the grid should handle this themselves.
 */
template <typename T> class Grid {
public:
  int RowCount() const { return 0; };
  int ColumnCount(const int row) const { return 0; }
  constexpr int PrevX(const int x, const int row) const {
    if (x == 0) {
      return ColumnCount(row) - 1;
    }
    return x - 1;
  }
  constexpr int NextX(const int x, const int row) const {
    if (x == ColumnCount(row) - 1) {
      return 0;
    }
    return x + 1;
  }
};

template <> int Grid<grids::Regular64>::RowCount() const { return 64; }
template <> int Grid<grids::Regular96>::RowCount() const { return 64; }

template <> int Grid<grids::Regular64>::ColumnCount(const int _row) const {
  return 64;
}
template <> int Grid<grids::Regular96>::ColumnCount(const int _row) const {
  return 96;
}

} // namespace circular