#include "../segment.h"

geometry::Segment &geometry::Segment::Move(const geometry::Vector &vector) {
  first_.x_ += vector.x_;
  first_.y_ += vector.y_;
  second_.x_ += vector.x_;
  second_.y_ += vector.y_;
  return *this;
}

bool geometry::Segment::ContainsPoint(const geometry::Point &point) const {
  return point.CrossesSegment(*this);
}

bool geometry::Segment::CrossesSegment(const geometry::Segment &segment) const {
  if (segment.first_.ContainsPoint(segment.second_) && first_.ContainsPoint(second_)) {
    return segment.first_.ContainsPoint(first_);
  }
  if (segment.first_.ContainsPoint(segment.second_)) {
    return segment.first_.CrossesSegment(*this);
  }
  if (first_.ContainsPoint(second_)) {
    return first_.CrossesSegment(segment);
  }
  int64_t x = (segment.second_.x_ - segment.first_.x_) * (first_.y_ - segment.first_.y_) -
              (segment.second_.y_ - segment.first_.y_) * (first_.x_ - segment.first_.x_);
  int64_t y = (second_.x_ - first_.x_) * (first_.y_ - segment.first_.y_) -
              (second_.y_ - first_.y_) * (first_.x_ - segment.first_.x_);
  int64_t distance = (segment.second_.y_ - segment.first_.y_) * (second_.x_ - first_.x_) -
                     (segment.second_.x_ - segment.first_.x_) * (second_.y_ - first_.y_);
  bool first_point_higher = std::max(std::min(first_.x_, second_.x_), std::min(segment.first_.x_, segment.second_.x_)) >
                            std::min(std::max(first_.x_, second_.x_), std::max(segment.first_.x_, segment.second_.x_));
  bool second_point_higher =
      std::max(std::min(first_.y_, second_.y_), std::min(segment.first_.y_, segment.second_.y_)) >
      std::min(std::max(first_.y_, second_.y_), std::max(segment.first_.y_, segment.second_.y_));
  if (first_point_higher || second_point_higher) {
    return false;
  }
  if (distance == 0) {
    return x == 0;
  }
  if (distance < 0) {
    x = -x;
    y = -y;
    distance = -distance;
  }
  return x >= 0 && y >= 0 && x <= distance && y <= distance;
}

std::unique_ptr<geometry::IShape> geometry::Segment::Clone() const {
  return std::make_unique<Segment>(first_, second_);
}

std::string geometry::Segment::ToString() const {
  return "Segment(" + first_.ToString() + ", " + second_.ToString() + ")";
}
