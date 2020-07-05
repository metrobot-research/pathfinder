#ifndef _path_h_
#define _path_h_
#include <ostream>
#include <vector>

#include "vec.hpp"
#include "circle.hpp"

/**
 * A Path encapsulates the data associated with following a specified set of
 * points.
 */
class Path {
 public:
  Path(std::vector<Vec> points);
  std::pair<Circle, Vec> circle_to_follow(Vec pos, Vec heading);
  std::string to_string();

 private:
  std::pair<Vec, Vec> next_lookahead(Vec pos);
  std::vector<Vec> path;
  static const double LOOKAHEAD_DISTANCE;
  std::pair<Vec, int> closest_point_on_path(Vec pos);
};

Path generate_path(Vec start_pos, Vec start_derivative, Vec end_pos, Vec end_derivative, int steps);

std::ostream &operator<<(std::ostream &os, Path p);

#endif  // _path_h_
