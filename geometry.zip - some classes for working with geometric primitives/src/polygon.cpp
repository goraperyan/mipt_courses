#include "../polygon.h"
#include "../segment.h"

geometry::Polygon& geometry::Polygon::Move(const geometry::Vector& vector) {
  for (size_t i = 0; i < polygon_.size(); ++i) {
    polygon_[i].Move(vector);
  }
  return *this;
}

bool geometry::Polygon::ContainsPoint(const geometry::Point& point) const {
  for (size_t i = 0; i < polygon_.size() - 1; ++i) {
    if (point.CrossesSegment(Segment(polygon_[i], polygon_[(i + 1)]))) {
      return true;
    }
  }
  if (point.CrossesSegment(Segment(polygon_[polygon_.size() - 1], polygon_[0]))) {
    return true;
  }
  size_t counter = 0;
  Segment segment(point, point + Vector(1, 100000000000000));
  for (size_t i = 0; i < polygon_.size() - 1; ++i) {
    if (segment.CrossesSegment(Segment(polygon_[i], polygon_[(i + 1)]))) {
      ++counter;
    }
  }
  if (segment.CrossesSegment(Segment(polygon_[polygon_.size() - 1], polygon_[0]))) {
    ++counter;
  }
  return counter % 2 != 0;
}

bool geometry::Polygon::CrossesSegment(const geometry::Segment& segment) const {
  for (size_t i = 0; i < polygon_.size() - 1; ++i) {
    if (segment.CrossesSegment(Segment(polygon_[i], polygon_[i + 1]))) {
      return true;
    }
  }
  if (segment.CrossesSegment(Segment(polygon_[polygon_.size() - 1], polygon_[0]))) {
    return true;
  }
  return false;
}

std::unique_ptr<geometry::IShape> geometry::Polygon::Clone() const {
  return std::make_unique<Polygon>(polygon_);
}

std::string geometry::Polygon::ToString() const {
  std::string str;
  for (size_t i = 0; i < polygon_.size() - 1; ++i) {
    str += polygon_[i].ToString();
    str += ", ";
  }
  return "Polygon(" + str + polygon_[polygon_.size() - 1].ToString() + ")";
}