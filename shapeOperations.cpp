#include "shapeOperations.hpp"
#include <iostream>

void kuznetsov::scale(const point_t& point, double k, std::unique_ptr< Shape >& shape)
{
  if (k <= 0.0) {
    throw std::logic_error("Incorrect value for k!");
  }
  point_t center1 = shape->getFrameRect().pos_;
  shape->move(point);
  point_t center2 = shape->getFrameRect().pos_;
  double x = center2.x_ - center1.x_;
  double y = center2.y_ - center1.y_;
  shape->scale(k);
  shape->move(-x * k, -y * k);
}

double kuznetsov::getSummaryArea(const kuznetsov::Storage< std::unique_ptr< Shape > >& storage)
{
  double area = 0.0;
  for (size_t i = 0; i < storage.getSize(); ++i) {
    area += storage[i]->getArea();
  }
  return area;
}

std::pair< kuznetsov::point_t, kuznetsov::point_t > kuznetsov::getCoordinatesOfFrame(
  const kuznetsov::rectangle_t& rectangle)
{
  point_t center = rectangle.pos_;
  point_t left{center.x_ - rectangle.width_ / 2.0, center.y_ - rectangle.height_ / 2.0};
  point_t right{center.x_ + rectangle.width_ / 2.0, center.y_ + rectangle.height_ / 2.0};
  return std::pair< point_t, point_t >(left, right);
}

void kuznetsov::printCoordinatesOfFrame(const kuznetsov::Storage< std::unique_ptr< Shape > >& storage, std::ostream& os)
{
  size_t size = storage.getSize();
  for (size_t i = 0; i < size; ++i) {
    auto pointPair = getCoordinatesOfFrame(storage[i]->getFrameRect());
    os << pointPair.first << " " << pointPair.second;
    if (i != size - 1) {
      os << " ";
    }
  }
}

void kuznetsov::printShapes(const kuznetsov::Storage< std::unique_ptr< Shape > >& storage, std::ostream& os)
{
  os << kuznetsov::getSummaryArea(storage) << " ";
  kuznetsov::printCoordinatesOfFrame(storage, os);
}
