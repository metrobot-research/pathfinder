#include <cmath>
#include <iostream>
#include <vector>

#include "path.hpp"
#include "vec.hpp"

/**
 * Simulate simulates the actual location of a vehicle as it attempts to follow
 * a given path using pure pursuit. Given a start position and heading, the
 * vehicle is simulated to be moving at the given speed (where speed is the
 * magnitude of movement it makes per time step).
 */
std::vector<Vec> simulate(Path path, Vec start_pos, Vec start_heading, double speed) {
  std::vector<Vec> locs;
  Vec pos = start_pos;
  Vec heading = start_heading;

  int i = 0;
  while (i < 100) {
    locs.push_back(pos);
    std::pair<double, Vec> path_info = path.curvature(pos);
    Vec center = path_info.second;
    double curvature = path_info.first;
    double radius = 1 / curvature;

    // Debug
    cout << " (x-" << center.x() << ")^2 + (y-" << center.y() << ")^2 = " << radius * radius << " ";

    // The change in angle of the vehicle with respect to the center of the
    // circle (s = r * theta).
    double angle_change = -speed / radius;

    // Treat the center of the circle as the origin, and find the new
    // coordinates with respect to this center.
    double rel_x = pos.x() - center.x();
    double rel_y = pos.y() - center.y();

    double new_x = rel_x * cos(angle_change) + rel_y * sin(angle_change);
    double new_y = -rel_x * sin(angle_change) + rel_y * cos(angle_change);

    pos = Vec(new_x + center.x(), new_y + center.y());

    i++;
  }
  return locs;
}
