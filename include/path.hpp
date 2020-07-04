#ifndef _path_h_
#define _path_h_
#include <ostream>
#include "vec.hpp"
#include <vector>

/**
 * A Path encapsulates the data associated with following a specified set of points.
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

std::ostream& operator<<(std::ostream& os, Path p);

#endif // _path_h_
