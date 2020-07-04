#include "vec.hpp"

#include <cmath>
#include <ostream>
#include <string>
using namespace std;

Vec::Vec(double ix, double iy) {
  this->x_coord = ix;
  this->y_coord = iy;
}

Vec::Vec() {
  this->x_coord = 0;
  this->y_coord = 0;
}

double Vec::x() {
  return this->x_coord;
}

double Vec::y() {
  return this->y_coord;
}

double Vec::magnitude() {
  return sqrt(this->x_coord * this->x_coord + this->y_coord * this->y_coord);
}

Vec Vec::unit() {
  double mag = this->magnitude();
  return Vec(this->x_coord / mag, this->y_coord / mag);
}

string Vec::to_string() {
  return std::to_string(this->x_coord) + "," + std::to_string(this->y_coord);
}

void Vec::set_x(double ix) {
  this->x_coord = ix;
}

void Vec::set_y(double iy) {
  this->y_coord = iy;
}

/**
 * Given a point specified by a vector, find the distance from the point
 * specified by this vector to that point. Simply use the distance formula.
 */
double Vec::distance_to(Vec next) {
  return sqrt((next.x() - this->x()) * (next.x() - this->x()) +
              (next.y() - this->y()) * (next.y() - this->y()));
}

/**
 * Determine whether if the point specified by this vector is between two other
 * points.
 */
bool Vec::is_between(Vec v1, Vec v2) {
  if (v1.x() > v2.x()) {
    if (this->x() > v1.x() || this->x() < v2.x()) return false;
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

ostream &operator<<(ostream &os, Vec v) {
  os << v.to_string();
  return os;
}

/**
 * Performs scalar multiplication on this vector.
 */
Vec operator*(double mult, Vec v) {
  Vec out = Vec(v.x() * mult, v.y() * mult);
  return out;
}

/**
 * Performs scalar multiplication on this vector.
 */
Vec operator*(Vec v, double mult) {
  Vec out = Vec(v.x() * mult, v.y() * mult);
  return out;
}

Vec operator+(Vec v1, Vec v2) {
  Vec out = Vec(v1.x() + v2.x(), v1.y() + v2.y());
  return out;
}

Vec operator-(Vec v1, Vec v2) {
  Vec out = Vec(v1.x() - v2.x(), v1.y() - v2.y());
  return out;
}

bool operator==(Vec v1, Vec v2) {
  return v1.y() == v2.y() && v1.y() == v2.y();
}

bool operator!=(Vec v1, Vec v2) {
  return !(v1 == v2);
}
