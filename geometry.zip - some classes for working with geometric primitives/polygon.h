#pragma once
#include "ishape.h"
#include "point.h"
#include "vector.h"
#include <vector>

namespace geometry {
class Polygon : public IShape {
 public:
  std::vector<Point> polygon_;
  Polygon() = default;
  explicit Polygon(const std::vector<Point> &polygon) : polygon_(polygon) {
  }
  Polygon &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry