#include "rectangle.hpp"

kuznetsov::Rectangle::Rectangle(const kuznetsov::point_t& left, const kuznetsov::point_t& right):
  left_(left),
  right_(right)
{
  if (left.x_ > right.x_ || left.y_ > right.y_) {
    throw std::logic_error("Incorrect coordinates to create rectangle!");
  }
}

kuznetsov::point_t kuznetsov::Rectangle::getCenter() const
{
  return kuznetsov::point_t{(right_.x_ + left_.x_) / 2.0, (right_.y_ + left_.y_) / 2.0};
}

double kuznetsov::Rectangle::getWidth() const
{
  return std::abs(left_.x_ - right_.x_);
}

double kuznetsov::Rectangle::getHeight() const
{
  return std::abs(left_.y_ - right_.y_);
}

double kuznetsov::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

void kuznetsov::Rectangle::move(double x, double y)
{
  movePoint(left_, x, y);
  movePoint(right_, x, y);
}

void kuznetsov::Rectangle::move(const kuznetsov::point_t& point)
{
  point_t center = getCenter();
  move(point.x_ - center.x_, point.y_ - center.y_);
}

kuznetsov::rectangle_t kuznetsov::Rectangle::getFrameRect() const
{
  return kuznetsov::rectangle_t{getCenter(), getWidth(), getHeight()};
}

void kuznetsov::Rectangle::doScale(double k)
{
  point_t center = getCenter();
  left_ = moveRelatively(center, left_, k);
  right_ = moveRelatively(center, right_, k);
}
