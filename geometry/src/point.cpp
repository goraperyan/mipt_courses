#include "../point.h"
#include "../segment.h"

geometry::Point &geometry::Point::Move(const Vector &vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

bool geometry::Point::ContainsPoint(const Point &point) const {
  return (x_ == point.x_) && (y_ == point.y_);
}

bool geometry::Point::CrossesSegment(const geometry::Segment &segment) const {
  if (segment.first_.x_ == segment.second_.x_ && segment.first_.y_ == segment.second_.y_) {
    return ContainsPoint(segment.first_);
  }
  Vector first = *this - segment.first_;
  Vector second = *this - segment.second_;
  return VectorMultiplication(first, second) == 0 && ScalarMultiplication(first, second) <= 0;
}

std::unique_ptr<geometry::IShape> geometry::Point::Clone() const {
  return std::make_unique<Point>(x_, y_);
}

std::string geometry::Point::ToString() const {
  return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

geometry::Point geometry::operator+(const geometry::Point &begin, const geometry::Vector &vector) {
  return {begin.x_ + vector.x_, begin.y_ + vector.y_};
}

geometry::Vector geometry::operator-(const geometry::Point &end, const geometry::Point &begin) {
  return {end.x_ - begin.x_, end.y_ - begin.y_};
}
