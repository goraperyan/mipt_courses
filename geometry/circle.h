#pragma once
#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Circle : public IShape {
 public:
  Point center_;
  int64_t radius_;
  Circle() = default;
  Circle(const Point &center, int64_t rad) : center_(center), radius_(rad) {
  }
  Circle &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry