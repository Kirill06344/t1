#ifndef SHAPE_OPERATIONS_HPP
#define SHAPE_OPERATIONS_HPP

#include "pointOperations.hpp"
#include "shape.hpp"

namespace kuznetsov {
  using shape_ptr = std::unique_ptr< kuznetsov::Shape >;
  void scale(const point_t& point, double k, std::unique_ptr< Shape >& shape);
  double getSummaryArea(const std::unique_ptr< shape_ptr[] >& shapeStorage, const size_t& size);
  std::pair< point_t, point_t > getCoordinatesOfFrame(const rectangle_t& rectangle);
  void printCoordinatesOfFrame(const std::unique_ptr< shape_ptr[] >& shapeStorage, const size_t& size, std::ostream& os);
  void printShapes(const std::unique_ptr< shape_ptr[] >& shapeStorage, const size_t& size, std::ostream& os);
}
#endif
