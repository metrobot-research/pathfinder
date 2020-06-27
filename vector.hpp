#ifndef _vector_h_
#define _vector_h_
#include <ostream>

using namespace std;

class Vector {
  public:
    Vector();
    Vector(double ix, double iy);
    double x();
    double y();
    void set_x(double ix);
    void set_y(double iy);
    double magnitude();
    string to_string();
    Vector unit();
    double distanceTo(Vector next);
    bool isBetween(Vector v1, Vector v2);
  private:
    double x_coord;
    double y_coord;
};

std::ostream& operator<<(std::ostream& os, Vector v);
Vector operator*(double mult, Vector v);
Vector operator*(Vector v, double mult);
Vector operator+(Vector v1, Vector v2);
Vector operator-(Vector v1, Vector v2);
bool operator==(Vector v1, Vector v2);
bool operator !=(Vector v1, Vector v2);

#endif // _vecto_h_r
