#include "path.hpp"
#include "util.hpp"
#include <cmath>
#include <iostream>
#include <vector>

const double Path::LOOKAHEAD_DISTANCE = 5;

/**
 * Fit a cubic function given specified starting and ending coordinates and
 * derivatives. Hermite polynomials are used to create the cubic fit.
 */
std::vector<Vec> hermite_cubic(Vec start_pos, Vec start_heading, Vec end_pos,
                               Vec end_heading, int steps) {
  std::vector<Vec> out;

  for (int t = 0; t < steps; t++) {
    double s = (double)t / (double)steps;
    double a1 = 2.0 * s * s * s - 3.0 * s * s + 1.0;
    double a2 = -2.0 * s * s * s + 3.0 * s * s;
    double a3 = s * s * s - 2.0 * s * s + s;
    double a4 = s * s * s - s * s;

    out.push_back(a1 * start_pos + a2 * end_pos + a3 * start_heading +
                  a4 * end_heading);
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
Path generate_path(Vec start_pos, Vec start_heading, Vec end_pos,
                   Vec end_heading, int steps) {
  return Path(
      hermite_cubic(start_pos, start_heading, end_pos, end_heading, steps));
}

Path::Path(std::vector<Vec> path) { this->path = path; }

string Path::to_string() {
  string out;
  std::vector<Vec> v = this->path;

  for (int i = 0; i < v.size(); i++) {
    out.append(v.at(i).to_string() + "\n");
  }

  return out;
}

/**
 * Given the current position (in global coordinates), return the curvature to
 * take in order to follow the path, as well as the center of the circle that
 * will be followed if this curvature is used.
 *
 * The curvature formula is derived from geometry: it's derivation can be found
 * in the CMU paper in the README references.
 */
std::pair<double, Vec> Path::curvature(Vec pos) {
  Vec goal = this->next_lookahead(pos);
  double dist = pos.distance_to(goal);

  // Convert goal to local coordinates (pos is the origin).
  Vec local_goal = goal - pos;

  double c = (2 * local_goal.x()) / (dist * dist);
  return std::make_pair(c,
                        centers_from_points_and_radius(pos, goal, 1 / c).first);
}

/**
 * Finds the next lookahead point on the path given a current position in global
 * coordinates.
 *
 * The closest point on the path to the current position is first found, and
 * then the point on the path that is one lookahead distance away from this
 * closest point is determined.
 *
 * This is done by iterating through all points on the path after the determined
 * start point and choosing the point on the path whose distance from the start
 * is closest to the lookahead distance.
 */

Vec Path::next_lookahead(Vec pos) {
  auto closest = this->closest_point_on_path(pos);
  Vec start = closest.first;
  int start_index = closest.second;
  double lookahead = Path::LOOKAHEAD_DISTANCE;

  if (start_index == this->path.size() - 1) {
    return start;
  }

  double min_lookahead_diff =
      abs(lookahead - start.distance_to(this->path.at(start_index + 1)));
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

  return this->path.at(min_index);
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
