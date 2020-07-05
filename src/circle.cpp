#include "circle.hpp"

#include "vec.hpp"

Circle::Circle() {
  this->c = Vec();
  this->r = 0;
}

Circle::Circle(Vec center, double radius) {
  this->c = center;
  this->r = radius;
}

Vec Circle::center() {
  return this->c;
}

double Circle::radius() {
  return this->r;
}

/**
 * Return a unit vector tangent to the circle at the given point.
 */
Vec Circle::unit_tangent_at(Vec pos) {
  double tangent_slope = -(this->c.x() - pos.x()) / (this->c.y() - pos.y());
  return Vec(1, tangent_slope).unit();
}
