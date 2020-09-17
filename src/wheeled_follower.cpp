#include "wheeled_follower.hpp"

#include "circle.hpp"
#include "path.hpp"

WheeledFollower::WheeledFollower(double width, Path path) : path(path) {
  this->width = width;
  this->path = path;
}

std::pair<double, double> WheeledFollower::rpms(Vec pos, Vec heading) {
  return this->velocity_proportions(pos, heading);
}

/**
 * Given a current position and heading, determine the circle to follow, figure out a
 * speed proportion (ratio of speeds) that must be followed, and then determine relevant directions
 * for each side of the robot to move.
 */
std::pair<double, double> WheeledFollower::velocity_proportions(Vec pos, Vec heading) {
  std::pair<Circle, Vec> path_info = path.circle_to_follow(pos, heading);
  Circle circle = path_info.first;
  Vec circle_heading = path_info.second;

  // s = r*theta, arclengths in a ratio
  double speed_ratio =
      (circle.radius() + (this->width / 2)) / (circle.radius() - (this->width / 2));


  if (circle.unit_tangent_at(pos).dot(circle_heading) < 0) {
  }

  return std::make_pair(0, 0);
}
