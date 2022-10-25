#include "pointOperations.hpp"
#include <iostream>
#include <cmath>

namespace {
  double getPartOfPoint(std::string& str)
  {
    size_t pos = str.find(' ');
    double crdt = std::stod(str.substr(0, pos));
    pos = (pos == std::string::npos) ? std::string::npos : pos + 1;
    str.erase(0, pos);
    return crdt;
  }
}

double kuznetsov::getLength(const kuznetsov::point_t& point1, const kuznetsov::point_t& point2)
{
  return std::sqrt(std::pow(point1.x_ - point2.x_, 2) + (point1.y_ - point2.y_, 2));
}

void kuznetsov::movePoint(point_t& point, double x, double y)
{
  point.x_ += x;
  point.y_ += y;
}

kuznetsov::point_t kuznetsov::moveRelatively(const kuznetsov::point_t& center, const kuznetsov::point_t& point,
                                             double k)
{
  double x = center.x_ + k * (point.x_ - center.x_);
  double y = center.y_ + k * (point.y_ - center.y_);
  return kuznetsov::point_t{x, y};
}

bool kuznetsov::operator==(const kuznetsov::point_t& lhs, const kuznetsov::point_t& rhs)
{
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

std::ostream& kuznetsov::operator<<(std::ostream& os, const kuznetsov::point_t& point)
{
  os << point.x_ << " " << point.y_;
  return os;
}

kuznetsov::point_t kuznetsov::getPointFromString(std::string& line)
{
  double x = getPartOfPoint(line);
  double y = getPartOfPoint(line);
  return point_t{x, y};
}

double kuznetsov::getAreaOfTriangle(const kuznetsov::point_t& p1, const kuznetsov::point_t& p2, const kuznetsov::point_t& p3)
{
  double s1 = kuznetsov::getLength(p1, p2);
  double s2 = kuznetsov::getLength(p2, p3);
  double s3 = kuznetsov::getLength(p1, p3);
  double p = (s1 + s2 + s3) / 2;
  return std::sqrt(p * (p - s1) * (p - s2) * (p - s3));
}
