#include "vec.hpp"
#include "path.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iterator>

/**
 * Fit a cubic function given specified starting and ending coordinates and derivatives. Hermite
 * polynomials are used to create the cubic fit.
 */
std::vector<Vec> hermite_cubic(Vec start_pos, Vec start_tan, Vec end_pos, Vec end_tan, int steps) {
    std::vector<Vec > out;

  for (int t=0; t<steps; t++) {
    double s = (double)t / (double)steps;
    double a1 = 2.0*s*s*s - 3.0*s*s + 1.0;
    double a2 = -2.0*s*s*s + 3.0*s*s;
    double a3 = s*s*s - 2.0*s*s + s;
    double a4 = s*s*s -  s*s;

    out.push_back(a1*start_pos + a2*end_pos + a3*start_tan + a4*end_tan);
  }

  return out;
}

/**
 * Given starting and ending positions, and derivatives, generate a path between them.
 *
 * This is a function that just delegates to one of the point generation functions such as
 * hermite_cubic.
 */
Path generate_path(Vec start_pos, Vec start_heading, Vec end_pos, Vec end_heading, int steps) {
    return Path(hermite_cubic(start_pos, start_heading, end_pos, end_heading, steps));
}

int main() {
    Path path = generate_path(Vec(0,0), Vec(40,0), Vec(30, 30), Vec(40, 0), 30);
    cout << path << "\n";

    std::pair<double, Vec> path_info = path.curvature(Vec(10, 10));
    
    cout << "curvature: " << path_info.first << "\tcenter: " << path_info.second;


    return 0;
}
