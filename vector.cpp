#include "vector.hpp"
#include <ostream>
#include <cmath>
#include <string>
using namespace std;

Vector::Vector(double ix, double iy) {
  this->x_coord = ix;
  this->y_coord = iy;
}

Vector::Vector() {
  this->x_coord = 0;
  this->y_coord = 0;
}

double Vector::x() {
  return this->x_coord;
}
    
double Vector::y() {
  return this->y_coord;
}

double Vector::magnitude() {
  return sqrt(this->x_coord*this->x_coord + this->y_coord*this->y_coord);
}

Vector Vector::unit() {
  double mag = this->magnitude();
  return Vector(this->x_coord/mag, this->y_coord/mag);
}

string Vector::to_string() {
  return std::to_string(this->x_coord) + "," + std::to_string(this->y_coord);
}

void Vector::set_x(double ix) {
  this->x_coord = ix;
}

void Vector::set_y(double iy) {
  this->y_coord = iy;
}

/**
 * Given a point specified by a vector, find the distance from the point specified by this vector to
 * that point. Simply use the distance formula.
 */
double Vector::distanceTo(Vector next) {
  return sqrt(
    (next.x() - this->x()) * (next.x() - this->x()) +
    (next.y() - this->y()) * (next.y() - this->y())
  );
}

/**
 * Determine whether if the point specified by this vector is between two other points.
 */
bool Vector::isBetween(Vector v1, Vector v2) {
  if (v1.x() > v2.x())  {
    if(this->x() > v1.x() || this->x() < v2.x()) return false;
  } else if (v1.x() < v2.x()) {
    if (this->x() < v1.x() || this->x() > v2.x()) return false;
  } else {
    if (this->x() != v1.x()) return false;
  }

  if (v1.y() > v2.y()) {
    if (this->y() > v1.y() || this->y() < v2.y()) return false;
  } else if (v1.y() < v2.y()) {
    if (this->y() < v1.y() || this->y() > v2.y()) return false;
  } else {
    if (this->y() != v1.y()) return false;
  }

  return true;
}

ostream& operator<<(ostream& os, Vector v) {
  os << v.to_string();
  return os;
}

/**
 * Performs scalar multiplication on this vector.
 */
Vector operator*(double mult, Vector v) {
  Vector out = Vector(v.x()*mult, v.y()*mult);
  return out;
}

/**
 * Performs scalar multiplication on this vector.
 */
Vector operator*(Vector v, double mult) {
  Vector out = Vector(v.x()*mult, v.y()*mult);
  return out;
}

Vector operator+(Vector v1, Vector v2) {
  Vector out = Vector(v1.x()+v2.x(), v1.y()+v2.y());
  return out;
}

Vector operator-(Vector v1, Vector v2) {
  Vector out = Vector(v1.x()-v2.x(), v1.y()-v2.y());
  return out;
}

bool operator==(Vector v1, Vector v2) {
  return v1.y()==v2.y() && v1.y()==v2.y();
}

bool operator !=(Vector v1, Vector v2) {
  return !(v1 == v2);
}
