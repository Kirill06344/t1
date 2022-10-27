#include <iostream>
#include <iomanip>
#include <string>
#include "concave.hpp"
#include "rectangle.hpp"
#include "complexquad.hpp"
#include "shapeOperations.hpp"
#include "shapeStorageSupport.hpp"

int main()
{
  std::streamsize precision = std::cout.precision();
  std::ios_base::fmtflags flags = std::cout.flags();
  std::unique_ptr< kuznetsov::shape_ptr[] > shapeStorage = std::make_unique< kuznetsov::shape_ptr[] >(0);
  size_t size = 0;
  size_t capacity = 0;
  bool existenceScale = false;
  while (!std::cin.eof()) {
    try {
      std::string line = "";
      std::getline(std::cin, line);
      if (!line.empty()) {
        size_t pos = line.find(' ');
        std::string command = line.substr(0, pos);
        line.erase(0, pos + 1);
        std::unique_ptr< kuznetsov::Shape > shape;
        if (command == "RECTANGLE") {
          kuznetsov::point_t left = kuznetsov::getPointFromString(line);
          kuznetsov::point_t right = kuznetsov::getPointFromString(line);
          shape = std::make_unique< kuznetsov::Rectangle >(left, right);
          kuznetsov::pushShape(std::move(shapeStorage), size, capacity, std::move(shape));
        } else if (command == "CONCAVE") {
          kuznetsov::point_t point1 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point2 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point3 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point4 = kuznetsov::getPointFromString(line);
          shape = std::make_unique< kuznetsov::Concave >(point1, point2, point3, point4);
          kuznetsov::pushShape(std::move(shapeStorage), size, capacity, std::move(shape));
        } else if (command == "COMPLEXQUAD") {
          kuznetsov::point_t point1 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point2 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point3 = kuznetsov::getPointFromString(line);
          kuznetsov::point_t point4 = kuznetsov::getPointFromString(line);
          shape = std::make_unique< kuznetsov::Complexquad >(point1, point2, point3, point4);
          kuznetsov::pushShape(std::move(shapeStorage), size, capacity, std::move(shape));
        } else if (command == "SCALE") {
          kuznetsov::point_t point = kuznetsov::getPointFromString(line);
          double k = std::stod(line.substr(0, line.find(' ')));
          std::cout << std::fixed << std::setprecision(1);
          kuznetsov::printShapes(shapeStorage, size, std::cout);
          std::cout << '\n';
          for (size_t i = 0; i < size; ++i) {
            kuznetsov::scale(point, k, shapeStorage[i]);
          }
          kuznetsov::printShapes(shapeStorage, size, std::cout);
          std::cout << std::setprecision(precision) << '\n';
          std::cout.flags(flags);
          existenceScale = true;
          break;
        }
      }
    } catch (const std::exception& ex) {
      std::cerr << ex.what() << "\n";
    }
  }
  if (size == 0 || !existenceScale) {
    std::cerr << "Invalid arguments for program!";
    return 1;
  }
  return 0;
}
