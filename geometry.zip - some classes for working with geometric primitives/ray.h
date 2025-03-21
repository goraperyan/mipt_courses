#pragma once
#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Ray : public IShape {
 public:
  Point begin_;
  Vector vector_;
  Ray() : begin_(Point(0, 0)), vector_(Vector(1, 0)) {
  }
  Ray(const Point &begin, const Point &end) : begin_(begin), vector_(end - begin) {
  }
  Ray &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  ~Ray() override = default;
};
}  // namespace geometry