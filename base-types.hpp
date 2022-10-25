#ifndef BASETYPES_HPP
#define BASETYPES_HPP

namespace kuznetsov {
  struct point_t {
    double x_;
    double y_;
  };

  struct rectangle_t {
    point_t pos_;
    double width_;
    double height_;
  };
}
#endif
