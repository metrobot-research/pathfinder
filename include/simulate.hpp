#ifndef _simulate_h_
#define _simulate_h_
#include <vector>

#include "path.hpp"
#include "vec.hpp"

std::vector<Vec> simulate(Path path, Vec start_pos, Vec start_velocity, double speed);
#endif  // _simulate_h_
