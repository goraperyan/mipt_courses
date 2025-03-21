#pragma once
#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Segment : public IShape {
 public:
  Point first_;
  Point second_;
  Segment(const Point &first, const Point &second) : first_(first), second_(second) {
  }
  Segment &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry