#include <cmath>
#include <iostream>
#include <vector>

#include "path.hpp"
#include "vec.hpp"
#include "circle.hpp"

/**
 * Simulate simulates the actual location of a vehicle as it attempts to follow
 * a given path using pure pursuit. Given a start position and heading (unit), the
 * vehicle is simulated to be moving at the given speed (where speed is the
 * magnitude of movement it makes per time step). The heading must be a unit vector.
 */
std::vector<Vec> simulate(Path path, Vec start_pos, Vec start_heading, double speed) {
  std::vector<Vec> locs;
  Vec pos = start_pos;
  Vec heading = start_heading;

  int i = 0;
  while (i < 20) {
    locs.push_back(pos);
    std::pair<Circle, Vec> path_info = path.circle_to_follow(pos, heading);
    Circle circle = path_info.first;
    Vec path_tangent = path_info.second;
    Vec center = circle.center();
    double radius = circle.radius();

    // Debug
    std::cout << "---\n(x-" << center.x() << ")^2 + (y-" << center.y() << ")^2 = " << radius * radius << "\n";
    std::cout << "path tangent: " << path_tangent << "\n";
    std::cout << "unit tangent: " << circle.unit_tangent_at(pos) << "\n";
    std::cout << "unit tangent dot: " << circle.unit_tangent_at(pos).dot(path_tangent) << "\n";
    std::cout << "radius: " << circle.radius() << "\n";
    std::cout << "pos: " << pos << "\n";

    // Figure out the next position of the vehicle
    // The change in angle of the vehicle with respect to the center of the
    // circle (s = r * theta).
    double angle_change = speed / radius;
    if (circle.unit_tangent_at(pos).dot(path_tangent) > 0) {
      angle_change = -angle_change;
    }

    // Treat the center of the circle as the origin, and find the new
    // coordinates with respect to this center.
    double rel_x = pos.x() - center.x();
    double rel_y = pos.y() - center.y();

    double new_rel_x = rel_x * cos(angle_change) + rel_y * sin(angle_change);
    double new_rel_y = -rel_x * sin(angle_change) + rel_y * cos(angle_change);

    pos = Vec(new_rel_x + center.x(), new_rel_y + center.y());
    heading = circle.unit_tangent_at(pos);

    i++;
  }
  return locs;
}
