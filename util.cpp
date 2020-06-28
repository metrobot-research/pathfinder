#include "util.hpp"
#include "vec.hpp"
#include <cmath>

/**
 * Return the two possibility for centers of a circle determined by two  points on its circumference
 * and its radius.
 *
 * Derivation of the formula:
 * https://math.stackexchange.com/questions/441450/how-to-find-arc-center-when-given-two-points-and-a-radius/441517#441517
 */
std::pair<Vec, Vec> centers_from_points_and_radius(Vec p1, Vec p2, double radius) {
  double x_mid = (p1.x() + p2.x()) / 2;
  double y_mid = (p1.y() + p2.y()) / 2;

  double dist = p1.distance_to(p2);

  double dx = p2.x() - p1.x();
  double dy = p2.y() - p1.y();

  double x1 = x_mid + sqrt(radius*radius / (dist*dist) - 1.0/4.0) * dy;
  double y1 = y_mid - sqrt(radius*radius / (dist*dist) - 1.0/4.0) * dx;

  double x2 = x_mid - sqrt(radius*radius / (dist*dist) - 1.0/4.0) * dy;
  double y2 = y_mid + sqrt(radius*radius / (dist*dist) - 1.0/4.0) * dx;

  return std::make_pair(Vec(x1, y1), Vec(x2, y2));
}
