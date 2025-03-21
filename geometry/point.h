#pragma once
#include "ishape.h"
#include "vector.h"

namespace geometry {
class Point : public IShape {
 public:
  int64_t x_;
  int64_t y_;
  Point() : x_(0), y_(0) {
  }
  Point(int64_t x, int64_t y) : x_(x), y_(y) {
  }
  Point &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  friend Point operator+(const Point &begin, const Vector &vector);
  friend Vector operator-(const Point &end, const Point &begin);
};

Point operator+(const Point &begin, const Vector &vector);
Vector operator-(const Point &end, const Point &begin);
}  // namespace geometry