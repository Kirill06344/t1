#include "shape.hpp"

void kuznetsov::Shape::scale(double k)
{
  if (k <= 0.0) {
    throw std::logic_error("Incorrect k for scale");
  }
  doScale(k);
}
