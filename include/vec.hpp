#ifndef _vector_h_
#define _vector_h_
#include <ostream>

class Vec {
 public:
  Vec();
  Vec(double ix, double iy);
  double x();
  double y();
  void set_x(double ix);
  void set_y(double iy);
  double magnitude();
  std::string to_string();
  Vec unit();
  double distance_to(Vec next);
  double dot(Vec v);

 private:
  double x_coord;
  double y_coord;
};

std::ostream &operator<<(std::ostream &os, Vec v);
Vec operator*(double mult, Vec v);
Vec operator*(Vec v, double mult);
Vec operator+(Vec v1, Vec v2);
Vec operator-(Vec v1, Vec v2);
bool operator==(Vec v1, Vec v2);
bool operator!=(Vec v1, Vec v2);

#endif  // _vector_h_
