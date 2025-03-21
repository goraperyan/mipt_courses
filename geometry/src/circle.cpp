#include "../circle.h"
#include "../line.h"
#include "../segment.h"

geometry::Circle &geometry::Circle::Move(const geometry::Vector &vector) {
  center_.x_ += vector.x_;
  center_.y_ += vector.y_;
  return *this;
}

bool geometry::Circle::ContainsPoint(const geometry::Point &point) const {
  return (point.x_ - center_.x_) * (point.x_ - center_.x_) + (point.y_ - center_.y_) * (point.y_ - center_.y_) <=
         radius_ * radius_;
}

bool geometry::Circle::CrossesSegment(const geometry::Segment &segment) const {
  if (segment.first_.x_ == segment.second_.x_ && segment.first_.y_ == segment.second_.y_) {
    return (segment.first_.x_ - center_.x_) * (segment.first_.x_ - center_.x_) +
               (segment.first_.y_ - center_.y_) * (segment.first_.y_ - center_.y_) ==
           radius_ * radius_;
  }
  if ((segment.first_.x_ - center_.x_) * (segment.first_.x_ - center_.x_) +
          (segment.first_.y_ - center_.y_) * (segment.first_.y_ - center_.y_) ==
      radius_ * radius_) {
    return true;
  }
  if ((segment.second_.x_ - center_.x_) * (segment.second_.x_ - center_.x_) +
          (segment.second_.y_ - center_.y_) * (segment.second_.y_ - center_.y_) ==
      radius_ * radius_) {
    return true;
  }
  if (ContainsPoint(segment.second_) && ContainsPoint(segment.first_)) {
    return false;
  }
  if (ContainsPoint(segment.second_) && !ContainsPoint(segment.first_)) {
    return true;
  }
  if (ContainsPoint(segment.second_) && !ContainsPoint(segment.first_)) {
    return true;
  }
  Line line(segment.first_, segment.second_);
  if ((line.a_ * center_.x_ + line.b_ * center_.y_ + line.c_) *
          (line.a_ * center_.x_ + line.b_ * center_.y_ + line.c_) >
      radius_ * radius_ * (line.a_ * line.a_ + line.b_ * line.b_)) {
    return false;
  }
  Line line2(center_, Point(center_.x_ + line.a_, center_.y_ + line.b_));
  return line2.CrossesSegment(segment);
}

std::unique_ptr<geometry::IShape> geometry::Circle::Clone() const {
  return std::make_unique<Circle>(center_, radius_);
}

std::string geometry::Circle::ToString() const {
  return "Circle(Point(" + std::to_string(center_.x_) + ", " + std::to_string(center_.y_) + "), " +
         std::to_string(radius_) + ")";
}
