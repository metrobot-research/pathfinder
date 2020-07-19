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
 * Return a unit vector tangent to the circle at the given point in the clockwise direction.
 */
Vec Circle::unit_tangent_at(Vec pos) {
  Vec r_vec = pos - this->center();
  double tangent_slope = -(this->c.x() - pos.x()) / (this->c.y() - pos.y());

  Vec tan = Vec(1, tangent_slope).unit();

  // Flip the vector as necessary to ensure it points in the clockwise direction.
  if (r_vec.x() > 0 && r_vec.y() > 0) {
    tan = -1 * tan;
  }
  if (r_vec.x() < 0 && r_vec.y() > 0) {
    tan = -1 * tan;
  }

  return tan;
}
