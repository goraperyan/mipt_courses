#include <iostream>
#include "cppstring.h"

String::String() : size_(0), capacity_(1), str_(nullptr) {
}

String::String(size_t size, char symbol) : size_(size), capacity_(size), str_(new char[size]) {
  for (size_t i = 0; i < size; ++i) {
    str_[i] = symbol;
  }
}

String::String(const char *str) : size_(strlen(str)), capacity_(size_), str_(new char[capacity_]) {
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = str[i];
  }
}

String::String(const char *str, size_t size) : size_(size), capacity_(size), str_(new char[size]) {
  for (size_t i = 0; i < size; ++i) {
    str_[i] = str[i];
  }
}

String::String(const String &other) : size_(other.size_), capacity_(other.capacity_), str_(new char[size_]) {
  for (size_t i = 0; i < size_; ++i) {
    str_[i] = other.str_[i];
  }
}

String::~String() {
  delete[] str_;
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
    auto *tmp = new char[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
      tmp[i] = str_[i];
    }
    delete[] str_;
    str_ = tmp;
  }
}

void String::Resize(size_t new_size, char symbol) {
  Reserve(new_size);
  if (size_ < new_size) {
    while (size_ < new_size) {
      str_[size_] = symbol;
      ++size_;
    }
  } else {
    size_ = new_size;
  }
}

void String::ShrinkToFit() {
  capacity_ = size_;
  auto *tmp = new char[size_];
  for (size_t i = 0; i < size_; ++i) {
    tmp[i] = str_[i];
  }
  delete[] str_;
  str_ = tmp;
}

char &String::At(size_t id) {
  if (id >= size_) {
    throw StringOutOfRange{};
  }
  return str_[id];
}

char String::At(size_t id) const {
  if (id >= size_) {
    throw StringOutOfRange{};
  }
  return str_[id];
}

char &String::Front() {
  return str_[0];
}

char String::Front() const {
  return str_[0];
}

char &String::Back() {
  return str_[size_ - 1];
}

char String::Back() const {
  return str_[size_ - 1];
}

char *String::CStr() const {
  return str_;
}

char *String::Data() const {
  return str_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String &other) {
  size_t tmp_size = size_;
  size_ = other.size_;
  other.size_ = tmp_size;

  size_t tmp_capacity = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = tmp_capacity;

  char *tmp_str = str_;
  str_ = other.str_;
  other.str_ = tmp_str;
}

void String::PopBack() {
  --size_;
}

void String::PushBack(char symbol) {
  if (size_ == capacity_) {
    Reserve(2 * capacity_);
  }
  str_[size_] = symbol;
  ++size_;
}

String &String::operator+=(const String &other) {
  Reserve(size_ + other.size_);
  for (size_t i = 0; i < other.size_; ++i) {
    str_[size_ + i] = other.str_[i];
  }
  size_ += other.size_;
  return *this;
}

String &String::operator=(const String &other) {
  String tmp(other);
  Swap(tmp);
  return *this;
}

char &String::operator[](size_t id) {
  return str_[id];
}

char String::operator[](size_t id) const {
  return str_[id];
}

String operator+(const String &first, const String &second) {
  String tmp(first);
  tmp += second;
  return tmp;
}

bool operator==(const String &first, const String &second) {
  if (first.size_ == second.size_) {
    for (size_t i = 0; i < first.size_; ++i) {
      if (first.str_[i] != second.str_[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool operator!=(const String &first, const String &second) {
  return !(first == second);
}

bool operator>(const String &first, const String &second) {
  if (first.size_ > second.size_) {
    return true;
  }
  if (first.size_ < second.size_) {
    return false;
  }
  for (size_t i = 0; i < first.size_; ++i) {
    if (first.str_[i] > second.str_[i]) {
      return true;
    }
    if (first.str_[i] < second.str_[i]) {
      return false;
    }
  }
  return false;
}

bool operator<(const String &first, const String &second) {
  if (first.size_ < second.size_) {
    return true;
  }
  if (first.size_ > second.size_) {
    return false;
  }
  for (size_t i = 0; i < first.size_; ++i) {
    if (first.str_[i] < second.str_[i]) {
      return true;
    }
    if (first.str_[i] > second.str_[i]) {
      return false;
    }
  }
  return false;
}

bool operator<=(const String &first, const String &second) {
  return !(first > second);
}

bool operator>=(const String &first, const String &second) {
  return !(first < second);
}

std::ostream &operator<<(std::ostream &os, const String &value) {
  for (size_t i = 0; i < value.size_; ++i) {
    os << value.str_[i];
  }
  return os;
}
