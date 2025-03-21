#pragma once
#include "ishape.h"
#include "vector.h"
#include "point.h"

namespace geometry {
class Line : public IShape {
 public:
  int64_t a_;
  int64_t b_;
  int64_t c_;
  Point point_;
  Vector direction_;
  Line() : a_(0), b_(1), c_(0) {
  }
  Line(const Point &first, const Point &second)
      : a_(first.y_ - second.y_)
      , b_(second.x_ - first.x_)
      , c_(second.y_ * first.x_ - second.x_ * first.y_)
      , point_(first)
      , direction_(second - first) {
  }
  Line &Move(const Vector &vector) override;
  bool ContainsPoint(const Point &point) const override;
  bool CrossesSegment(const Segment &segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry