#ifndef POINT_OPERATIONS_HPP
#define POINT_OPERATIONS_HPP

#include <cmath>
#include <iosfwd>
#include <memory>
#include "base-types.hpp"

namespace kuznetsov {
  double getLength(const point_t& point1, const point_t& point2);
  void movePoint(point_t& point, double x, double y);
  point_t moveRelatively(const point_t& p, const point_t& p1, double k);
  point_t getPointFromString(std::string& line);
  bool operator==(const point_t& lhs, const point_t& rhs);
  std::ostream& operator<<(std::ostream& os, const point_t& point);
  double getAreaOfTriangle(const kuznetsov::point_t& p1, const kuznetsov::point_t& p2, const kuznetsov::point_t& p3);
}
#endif
