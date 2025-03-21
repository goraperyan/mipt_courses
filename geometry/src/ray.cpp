#include "../line.h"
#include "../ray.h"
#include "../segment.h"

geometry::Ray &geometry::Ray::Move(const geometry::Vector &vector) {
  begin_.x_ += vector.x_;
  begin_.y_ += vector.y_;
  return *this;
}

bool geometry::Ray::ContainsPoint(const geometry::Point &point) const {
  return point.ContainsPoint(begin_) ||
         (VectorMultiplication(point - begin_, vector_) == 0 && ScalarMultiplication(point - begin_, vector_) > 0);
}

bool geometry::Ray::CrossesSegment(const geometry::Segment &segment) const {
  if (segment.first_.ContainsPoint(segment.second_) && vector_ == Vector(0, 0)) {
    return begin_.ContainsPoint(segment.first_);
  }
  if (segment.first_.ContainsPoint(segment.second_)) {
    return ContainsPoint(segment.first_);
  }
  if (vector_ == Vector(0, 0)) {
    return begin_.CrossesSegment(segment);
  }
  Line line(begin_, begin_ + vector_);
  Vector p_o = begin_ - segment.first_;
  Vector p_q = segment.second_ - segment.first_;
  int64_t p_o_p_q_vect_mult = VectorMultiplication(p_o, p_q);
  int64_t vect_p_q_vect_mult = VectorMultiplication(vector_, p_q);
  return segment.ContainsPoint(begin_) || ContainsPoint(segment.first_) || ContainsPoint(segment.second_) ||
         ((p_o_p_q_vect_mult * vect_p_q_vect_mult < 0) && line.CrossesSegment(segment));
}

std::unique_ptr<geometry::IShape> geometry::Ray::Clone() const {
  return std::make_unique<Ray>(begin_, begin_ + vector_);
}

std::string geometry::Ray::ToString() const {
  return "Ray(Point(" + std::to_string(begin_.x_) + ", " + std::to_string(begin_.y_) + "), Vector(" +
         std::to_string(vector_.x_) + ", " + std::to_string(vector_.y_) + "))";
}