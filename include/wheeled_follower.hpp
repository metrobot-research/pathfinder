#ifndef _wheeled_follower_h_
#define _wheeled_follower_h_

#include "path.hpp"
#include "vec.hpp"

/**
 * A wheeled follower defines a path follower with wheels.
 */
class WheeledFollower {
 public:
  WheeledFollower(double width, Path path);
  std::pair<double, double> rpms(Vec pos, Vec heading);

 private:
  std::pair<double, double> velocity_proportions(Vec pos, Vec heading);
  double width;
  Path path;
};

#endif  // _wheeled_follower_h_
