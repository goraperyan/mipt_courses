#include "../vector.h"

geometry::Vector geometry::Vector::operator+() const {
  return *this;
}

geometry::Vector geometry::Vector::operator-() const {
  return {-x_, -y_};
}

geometry::Vector operator+(const geometry::Vector &first, const geometry::Vector &second) {
  return {first.x_ + second.x_, first.y_ + second.y_};
}
geometry::Vector operator-(const geometry::Vector &first, const geometry::Vector &second) {
  return {first.x_ - second.x_, first.y_ - second.y_};
}

geometry::Vector geometry::Vector::operator*(const int64_t number) const {
  return {x_ * number, y_ * number};
}

geometry::Vector geometry::Vector::operator/(const int64_t number) const {
  return {x_ / number, y_ / number};
}

geometry::Vector &geometry::Vector::operator+=(const Vector &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

geometry::Vector &geometry::Vector::operator-=(const Vector &other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

geometry::Vector &geometry::Vector::operator*=(const int64_t number) {
  x_ *= number;
  y_ *= number;
  return *this;
}

geometry::Vector &geometry::Vector::operator/=(const int64_t number) {
  x_ /= number;
  y_ /= number;
  return *this;
}

bool geometry::operator==(const geometry::Vector &first, const geometry::Vector &second) {
  return (first.x_ == second.x_) && (first.y_ == second.y_);
}

int64_t geometry::VectorMultiplication(const geometry::Vector &first, const geometry::Vector &second) {
  return first.x_ * second.y_ - first.y_ * second.x_;
}

int64_t geometry::ScalarMultiplication(const geometry::Vector &first, const geometry::Vector &second) {
  return first.x_ * second.x_ + first.y_ * second.y_;
}