#ifndef _vector_h_
#define _vector_h_
#include <ostream>

using namespace std;

class Vec {
  public:
    Vec();
    Vec(double ix, double iy);
    double x();
    double y();
    void set_x(double ix);
    void set_y(double iy);
    double magnitude();
    string to_string();
    Vec unit();
    double distance_to(Vec next);
    bool is_between(Vec v1, Vec v2);
  private:
    double x_coord;
    double y_coord;
};

std::ostream& operator<<(std::ostream& os, Vec v);
Vec operator*(double mult, Vec v);
Vec operator*(Vec v, double mult);
Vec operator+(Vec v1, Vec v2);
Vec operator-(Vec v1, Vec v2);
bool operator==(Vec v1, Vec v2);
bool operator !=(Vec v1, Vec v2);

#endif // _vecto_h_r
