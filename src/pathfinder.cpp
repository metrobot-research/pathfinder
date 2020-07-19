#include <iostream>

#include "path.hpp"
#include "simulate.hpp"
#include "vec.hpp"

int main() {
  Path path = generate_path(Vec(0, 0), Vec(-40, 0), Vec(-30, -30), Vec(-40, 0), 30);
  std::cout << "Path:\n" << path << "\n";

  std::vector<Vec> locs = simulate(path, Vec(0, 0), Vec(-40, 0).unit(), 3);

  std::string out;
  for (int i = 0; i < locs.size(); i++) {
    out.append(locs.at(i).to_string() + "\n");
  }

  std::cout << "\nSimulated locations:\n" << out;

  return 0;
}
