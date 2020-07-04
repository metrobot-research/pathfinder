#ifndef _path_h_
#define _path_h_
#include <ostream>
#include <vector>

#include "vec.hpp"

/**
 * A Path encapsulates the data associated with following a specified set of
 * points.
 */
class Path {
 public:
  Path(std::vector<Vec> points);
  std::pair<double, Vec> curvature(Vec pos);
  string to_string();

 private:
  Vec next_lookahead(Vec pos);
  std::vector<Vec> path;
  static const double LOOKAHEAD_DISTANCE;
  std::pair<Vec, int> closest_point_on_path(Vec pos);
};

Path generate_path(Vec start_pos, Vec start_heading, Vec end_pos, Vec end_heading, int steps);

std::ostream &operator<<(std::ostream &os, Path p);

#endif  // _path_h_
