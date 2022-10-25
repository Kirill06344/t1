#include "concave.hpp"

namespace {
  bool isTriangle(const kuznetsov::point_t& p1, const kuznetsov::point_t& p2, const kuznetsov::point_t& p3)
  {
    double s1 = kuznetsov::getLength(p1, p2);
    double s2 = kuznetsov::getLength(p2, p3);
    double s3 = kuznetsov::getLength(p3, p1);
    return s1 + s2 + s3 > std::max(s1, std::max(s2, s3)) * 2;
  }

}

kuznetsov::Concave::Concave(const point_t& point1, const point_t& point2, const point_t& point3, const point_t& point4):
  point1_(point1),
  point2_(point2),
  point3_(point3),
  point4_(point4)
{
  if (!isTriangle(point1, point2, point3)) {
    throw std::logic_error("Invalid condition for create polygon!");
  }

  double part1 = (point1.x_ - point4.x_) * (point2.y_ - point1.y_) - (point2.x_ - point1.x_) * (point1.y_ - point4.y_);
  double part2 = (point2.x_ - point4.x_) * (point3.y_ - point2.y_) - (point3.x_ - point2.x_) * (point2.y_ - point4.y_);
  double part3 = (point3.x_ - point4.x_) * (point1.y_ - point3.y_) - (point1.x_ - point3.x_) * (point3.y_ - point4.y_);

  if (!((part1 > 0 && part2 > 0 && part3 > 0) || (part1 < 0 && part2 < 0 && part3 < 0))) {
    throw std::logic_error("Invalid condition for create polygon!");
  }
}

double kuznetsov::Concave::getArea() const
{
  return kuznetsov::getAreaOfTriangle(point1_, point2_, point3_) - getAreaOfTriangle(point2_, point3_, point4_);
}

void kuznetsov::Concave::move(double x, double y)
{
  kuznetsov::movePoint(point1_, x, y);
  kuznetsov::movePoint(point2_, x, y);
  kuznetsov::movePoint(point3_, x, y);
  kuznetsov::movePoint(point4_, x, y);
}

void kuznetsov::Concave::move(const kuznetsov::point_t& point)
{
  double x = point.x_ - point4_.x_;
  double y = point.y_ - point4_.y_;
  move(x, y);
}

kuznetsov::rectangle_t kuznetsov::Concave::getFrameRect() const
{
  double minX = (point1_.x_ < point2_.x_) ? std::min(point1_.x_, point3_.x_) : std::min(point2_.x_, point3_.x_);
  double maxX = (point1_.x_ > point2_.x_) ? std::max(point1_.x_, point3_.x_) : std::max(point2_.x_, point3_.x_);
  double minY = (point1_.y_ < point2_.y_) ? std::min(point1_.y_, point3_.y_) : std::min(point2_.y_, point3_.y_);
  double maxY = (point1_.y_ > point2_.y_) ? std::max(point1_.y_, point3_.y_) : std::max(point2_.y_, point3_.y_);
  point_t center_{(minX + maxX) / 2, (minY + maxY) / 2};
  rectangle_t rect{center_, maxX - minX, maxY - minY};
  return rect;
}

void kuznetsov::Concave::doScale(double k)
{
  point1_ = moveRelatively(point4_, point1_, k);
  point2_ = moveRelatively(point4_, point2_, k);
  point3_ = moveRelatively(point4_, point3_, k);

}
