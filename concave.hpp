#ifndef CONCAVE_HPP
#define CONCAVE_HPP

#include "shape.hpp"
#include <vector>

namespace kuznetsov {
  class Concave: public Shape {
    public:
    Concave() = delete;
    Concave(const point_t& point1, const point_t& point2, const point_t& point3, const point_t& point4);
    double getArea() const override;
    void move(double x, double y) override;
    void move(const point_t& point) override;
    rectangle_t getFrameRect() const override;
    void doScale(double k) override;
    private:
    point_t point1_;
    point_t point2_;
    point_t point3_;
    point_t point4_;
  };
}
#endif
