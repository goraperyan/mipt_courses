#pragma once
#include <iostream>

namespace geometry {
class Vector {
 public:
  int64_t x_;
  int64_t y_;
  Vector() : x_(0), y_(0) {
  }
  Vector(int64_t x, int64_t y) : x_(x), y_(y) {
  }
  Vector operator+() const;
  Vector operator-() const;
  Vector operator*(const int64_t number) const;
  Vector operator/(const int64_t number) const;
  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  Vector &operator*=(const int64_t number);
  Vector &operator/=(const int64_t number);
};

Vector operator+(const Vector &first, const Vector &second);
Vector operator-(const Vector &first, const Vector &second);
bool operator==(const Vector &first, const Vector &second);
int64_t VectorMultiplication(const Vector &first, const Vector &second);
int64_t ScalarMultiplication(const Vector &first, const Vector &second);
}  // namespace geometry