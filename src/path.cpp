#include "path.hpp"

#include <cmath>
#include <iostream>
#include <vector>

#include "circle.hpp"
#include "util.hpp"

const double Path::LOOKAHEAD_DISTANCE = 5;

/**
 * Fit a cubic function given specified starting and ending coordinates and
 * derivatives. Hermite polynomials are used to create the cubic fit.
 */
std::vector<Vec> hermite_cubic(Vec start_pos, Vec start_derivative, Vec end_pos, Vec end_derivative,
                               int steps) {
  std::vector<Vec> out;

  for (int t = 0; t < steps; t++) {
    double s = (double)t / (double)steps;
    double a1 = 2.0 * s * s * s - 3.0 * s * s + 1.0;
    double a2 = -2.0 * s * s * s + 3.0 * s * s;
    double a3 = s * s * s - 2.0 * s * s + s;
    double a4 = s * s * s - s * s;

    out.push_back(a1 * start_pos + a2 * end_pos + a3 * start_derivative + a4 * end_derivative);
  }

  return out;
}

/**
 * Given starting and ending positions, and derivatives, generate a path between
 * them.
 *
 * This is a function that just delegates to one of the point generation
 * functions such as hermite_cubic.
 */
Path generate_path(Vec start_pos, Vec start_derivative, Vec end_pos, Vec end_derivative,
                   int steps) {
  return Path(hermite_cubic(start_pos, start_derivative, end_pos, end_derivative, steps));
}

Path::Path(std::vector<Vec> path) {
  this->path = path;
}

std::string Path::to_string() {
  std::string out;
  std::vector<Vec> v = this->path;

  for (int i = 0; i < v.size(); i++) {
    out.append(v.at(i).to_string() + "\n");
  }

  return out;
}

/**
 * Given the current position (in global coordinates) and heading, return the circle to
 * follow in order to follow the path as well as the direction along which the circle should be
 * followed. The input heading is a unit vector.
 *
 *
 * The curvature formula is derived from geometry: it's derivation can be found
 * in the CMU paper in the README references. Given this curvature, the two potential circles that
 * have the curvature and pass through the input point are found. The correct tangent directions are
 * found (based on which more closely approximates the path), and then the tangent whose direction
 * most closely matches the heading is chosen.
 */
std::pair<Circle, Vec> Path::circle_to_follow(Vec pos, Vec heading) {
  std::pair<Vec, Vec> goal_tangent_pair = this->next_lookahead(pos);
  Vec goal = goal_tangent_pair.first;
  Vec path_tangent = goal_tangent_pair.second;
  double dist = pos.distance_to(goal);

  // Convert goal to local coordinates (pos is the origin).
  Vec local_goal = goal - pos;

  double k = (2 * std::abs(local_goal.x())) / (dist * dist);
  double radius = 1 / k;
  std::pair<Vec, Vec> centers = centers_from_points_and_radius(pos, goal, radius);

  // Choose the best tangent vector for each circle
  Circle circle_1 = Circle(centers.first, radius);
  Circle circle_2 = Circle(centers.second, radius);
  Vec heading_1_1 = circle_1.unit_tangent_at(pos);
  Vec heading_1_2 = -1 * circle_1.unit_tangent_at(pos);
  Vec heading_2_1 = circle_2.unit_tangent_at(pos);
  Vec heading_2_2 = -1 * circle_2.unit_tangent_at(pos);

  Vec heading_1;
  if (path_tangent.dot(heading_1_1) > path_tangent.dot(heading_1_2)) {
    heading_1 = heading_1_1;
  } else {
    heading_1 = heading_1_2;
  }

  Vec heading_2;
  if (path_tangent.dot(heading_2_1) > path_tangent.dot(heading_2_2)) {
    heading_2 = heading_2_1;
  } else {
    heading_2 = heading_2_2;
  }

  Vec circle_heading;

  // Have the two best tangent directions on the circles, now choose the best circle to follow.
  Circle circle;
  if (heading.dot(heading_1) > heading.dot(heading_2)) {
    circle_heading = heading_1;
    circle = circle_1;
  } else {
    circle_heading = heading_2;
    circle = circle_2;
  }

  return std::make_pair(circle, circle_heading);
}

/**
 * Finds the next lookahead point on the path given a current position in global
 * coordinates. Also finds and returns a unit vector tangent to the path at the closest point on
 * the path to the current position.
 *
 * The closest point on the path to the current position is first found, and
 * then the point on the path that is one lookahead distance away from this
 * closest point is determined.
 *
 * This is done by iterating through all points on the path after the determined
 * start point and choosing the point on the path whose distance from the start
 * is closest to the lookahead distance.
 */

std::pair<Vec, Vec> Path::next_lookahead(Vec pos) {
  std::pair<Vec, int> closest = this->closest_point_on_path(pos);
  Vec start = closest.first;
  int start_index = closest.second;
  double lookahead = Path::LOOKAHEAD_DISTANCE;

  if (start_index == this->path.size() - 1) {
    return std::make_pair(start, Vec());
  }

  Vec next = this->path.at(start_index + 1);

  Vec path_tangent = std::copysign(1, next.x() - start.x()) * Vec(1, (next.y() - start.y()) / (next.x() - start.x())).unit();

  double min_lookahead_diff = abs(lookahead - start.distance_to(this->path.at(start_index + 1)));
  int min_index = start_index + 1;

  // Find the point on the path whose distance from start is closest to the
  // lookahead distance.
  for (int i = start_index + 2; i < this->path.size(); i++) {
    Vec v = this->path.at(i);
    double dist = start.distance_to(v);

    if (abs(lookahead - dist) <= min_lookahead_diff) {
      min_lookahead_diff = abs(lookahead - dist);
      min_index = i;
    }
  }

  return std::make_pair(this->path.at(min_index), path_tangent);
}

/**
 * Find the closest point on the path to the current position (in global
 * coordinates), and return it and it's index in the path list.
 */
std::pair<Vec, int> Path::closest_point_on_path(Vec pos) {
  // This blatant inefficiency is temporary. It will be fixed once the proof of
  // concept is complete.
  double min_dist = pos.distance_to(this->path.at(0));
  int closest_index = 0;

  for (int i = 0; i < this->path.size(); i++) {
    Vec v = this->path.at(i);
    double dist = pos.distance_to(v);
    if (dist < min_dist) {
      min_dist = dist;
      closest_index = i;
    }
  }
  return std::make_pair(this->path.at(closest_index), closest_index);
}

std::ostream &operator<<(std::ostream &os, Path p) {
  os << p.to_string();
  return os;
}
