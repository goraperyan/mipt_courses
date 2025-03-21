#include "../line.h"
#include "../segment.h"

geometry::Line &geometry::Line::Move(const geometry::Vector &vector) {
  point_ = point_.Move(vector);
  c_ -= a_ * vector.x_ + b_ * vector.y_;
  return *this;
}

bool geometry::Line::ContainsPoint(const geometry::Point &point) const {
  return a_ * point.x_ + b_ * point.y_ + c_ == 0;
}

bool geometry::Line::CrossesSegment(const geometry::Segment &segment) const {
  return (a_ * segment.first_.x_ + b_ * segment.first_.y_ + c_) *
             (a_ * segment.second_.x_ + b_ * segment.second_.y_ + c_) <=
         0;
}

std::unique_ptr<geometry::IShape> geometry::Line::Clone() const {
  return std::make_unique<Line>(point_, point_ + direction_);
}

std::string geometry::Line::ToString() const {
  return "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
}
