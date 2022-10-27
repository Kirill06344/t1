#ifndef SHAPE_STORAGE_SUPPORT
#define SHAPE_STORAGE_SUPPORT

#include <memory>
#include <cmath>

namespace {
  const double goldenRatio = 1.618;
}

namespace kuznetsov {
  template< typename T >
  void pushShape(std::unique_ptr< T[] >&& shapeStorage, size_t& size, size_t& capacity, T&& shape)
  {
    if (capacity == size) {
      size_t newCapacity = std::ceil(goldenRatio * capacity) + 1;
      auto newStorage = std::make_unique< T[] >(newCapacity);
      for (size_t i = 0; i < size; ++i) {
        newStorage[i] = std::move(shapeStorage[i]);
      }
      shapeStorage = std::move(newStorage);
      capacity = newCapacity;
    }
    shapeStorage[size++] = std::move(shape);
  }

}

#endif
