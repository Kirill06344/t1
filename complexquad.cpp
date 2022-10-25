#include "complexquad.hpp"


namespace {
  bool isAnyEqualPoints(const kuznetsov::point_t& p1, const kuznetsov::point_t& p2, const kuznetsov::point_t& p3,
                        const kuznetsov::point_t& p4)
  {
    return (p1 == p2 || p1 == p3 || p1 == p4 || p2 == p3 || p2 == p4 || p3 == p4);
  }

  kuznetsov::point_t getIntersectionPoint(const kuznetsov::point_t& p1, const kuznetsov::point_t& p2,
                                          const kuznetsov::point_t& p3, const kuznetsov::point_t& p4)
  {
    kuznetsov::point_t inc;
    double n = 0;
    if (p2.y_ - p1.y_ != 0) {
      double q = (p2.x_ - p1.x_) / (p1.y_ - p2.y_);
      double sn = (p3.x_ - p4.x_) + (p3.y_ - p4.y_) * q;
      double fn = (p3.x_ - p1.x_) + (p2.y_ - p1.y_) * q;
      n = fn / sn;
    } else {
      if (p3.y_ - p4.y_ == 0) {
        throw std::logic_error("Parallel!");
      }
      n = (p3.y_ - p1.y_) / (p3.y_ - p4.y_);
    }
    inc.x_ = p3.x_ + (p4.x_ - p3.x_) * n;
    inc.y_ = p3.y_ + (p4.y_ - p3.y_) * n;
    return inc;
  }

}

kuznetsov::Complexquad::Complexquad(const point_t& point1, const point_t& point2, const point_t& point3,
                                    const point_t& point4):
  point1_(point1),
  point2_(point2),
  point3_(point3),
  point4_(point4)
{
  if (isAnyEqualPoints(point1, point2, point3, point4)) {
    throw std::logic_error("Invalid condition to create complexsquad!");
  }

  try {
    center_ = getIntersectionPoint(point1, point2, point3, point4);
  } catch (const std::exception& ex) {
    throw std::logic_error("Invalid condition to create complexsquad!");
  }

  if (center_ == point1 || center_ == point2 || center_ == point3 || center_ == point4) {
    throw std::logic_error("Invalid condition to create complexsquad!");
  }
}

double kuznetsov::Complexquad::getArea() const
{
  return kuznetsov::getAreaOfTriangle(point1_, point4_, center_) + getAreaOfTriangle(point2_, point3_, center_);
}

void kuznetsov::Complexquad::move(double x, double y)
{
  kuznetsov::movePoint(point1_, x, y);
  kuznetsov::movePoint(point2_, x, y);
  kuznetsov::movePoint(point3_, x, y);
  kuznetsov::movePoint(point4_, x, y);
  kuznetsov::movePoint(center_, x, y);
}

void kuznetsov::Complexquad::move(const kuznetsov::point_t& point)
{
  double x = point.x_ - center_.x_;
  double y = point.y_ - center_.y_;
  move(x, y);
}

kuznetsov::rectangle_t kuznetsov::Complexquad::getFrameRect() const
{
  double minX = point4_.x_;
  double maxX = point4_.x_;
  double minY = point4_.y_;
  double maxY = point4_.y_;
  minX = std::min(minX,
                  (point1_.x_ < point2_.x_) ? std::min(point1_.x_, point3_.x_) : std::min(point2_.x_, point3_.x_));
  maxX = std::max(maxX,
                  (point1_.x_ > point2_.x_) ? std::max(point1_.x_, point3_.x_) : std::max(point2_.x_, point3_.x_));
  minY = std::min(minY,
                  (point1_.y_ < point2_.y_) ? std::min(point1_.y_, point3_.y_) : std::min(point2_.y_, point3_.y_));
  maxY = std::max(maxY,
                  (point1_.y_ > point2_.y_) ? std::max(point1_.y_, point3_.y_) : std::max(point2_.y_, point3_.y_));
  point_t center{(minX + maxX) / 2, (minY + maxY) / 2};
  rectangle_t rect{center, maxX - minX, maxY - minY};
  return rect;
}

void kuznetsov::Complexquad::doScale(double k)
{
  point1_ = kuznetsov::moveRelatively(point1_, center_, k);
  point2_ = kuznetsov::moveRelatively(point2_, center_, k);
  point3_ = kuznetsov::moveRelatively(point3_, center_, k);
  point4_ = kuznetsov::moveRelatively(point4_, center_, k);

}
