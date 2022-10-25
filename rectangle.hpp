#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace kuznetsov {
  class Rectangle: public Shape {
    public:
    Rectangle() = delete;
    Rectangle(const point_t& left, const point_t& right);
    double getArea() const override;
    void move(double x, double y) override;
    void move(const point_t& point) override;
    rectangle_t getFrameRect() const override;
    void doScale(double k) override;
    private:
    point_t left_;
    point_t right_;
    point_t getCenter() const;
    double getWidth() const;
    double getHeight() const;
  };
}
#endif
