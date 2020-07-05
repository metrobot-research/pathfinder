#ifndef _circle_h_
#define _circle_h_
#include "vec.hpp"

class Circle {
  public:
    Circle();
    Circle(Vec center, double radius);
    Vec center();
    double radius();
    Vec unit_tangent_at(Vec pos);
  private:
    Vec c;
    double r;
};

#endif // _vector_h_
