#include "vec.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

/**
 * Fit a cubic function given specified starting and ending coordinates and derivatives. Hermite
 * polynomials are used to create the cubic fit.
 */
vector<Vec> hermiteCubic(Vec start_pos, Vec start_tan, Vec end_pos, Vec end_tan, int steps) {
  vector<Vec > out;

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

string vec_string(vector<Vec> v) {
  string out;

  for (int i=0; i<v.size(); i++) {
    out.append(v.at(i).to_string()+"\n");
  }

  return out;
}

int main() {
    vector<Vec> path = hermiteCubic(Vec(0,0), Vec(40,0), Vec(30,-10), Vec(40, 0), 30);
    cout << vec_string(path);

    return 0;
}
