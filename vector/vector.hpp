#pragma once

#include <iostream>
#include <iterator>

template <class T>
class Vector {
 private:
  size_t capacity_;
  size_t size_;
  T *buffer_;

 public:
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : capacity_(0), size_(0), buffer_(nullptr) {
  }

  explicit Vector(const size_t &size) : capacity_(size), size_(size), buffer_(nullptr) {
    if (size > 0) {
      buffer_ = new T[size];
    }
  }

  Vector(size_t size, T value) : capacity_(size), size_(size), buffer_(nullptr) {
    if (size > 0) {
      auto tmp = new T[size];
      try {
        for (size_t i = 0; i < size; i++) {
          tmp[i] = value;
          buffer_ = tmp;
        }
      } catch (...) {
        capacity_ = size;
        size_ = size;
        delete[] tmp;
        throw;
      }
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : capacity_(last - first), size_(last - first), buffer_(nullptr) {
    try {
      if (last - first > 0) {
        buffer_ = new T[last - first];
        size_t counter = 0;
        auto iter = first;
        while (iter != last) {
          buffer_[counter] = *iter;
          ++iter;
          ++counter;
        }
      }
    } catch (...) {
      delete[] buffer_;
      capacity_ = 0;
      size_ = 0;
      buffer_ = nullptr;
      throw;
    }
  }

  Vector(std::initializer_list<T> list) : capacity_(list.size()), size_(list.size()), buffer_(nullptr) {
    buffer_ = new T[capacity_];
    try {
      for (size_t i = 0; i < size_; ++i) {
        buffer_[i] = *(list.begin() + i);
      }
    } catch (...) {
      delete[] buffer_;
      size_ = 0;
      capacity_ = 0;
      buffer_ = nullptr;
      throw;
    }
  }

  Vector(Vector &&other) noexcept : capacity_(other.capacity_), size_(other.size_), buffer_(other.buffer_) {
    other.capacity_ = 0;
    other.size_ = 0;
    other.buffer_ = nullptr;
  }

  Vector(const Vector &other) : capacity_(other.capacity_), size_(other.size_), buffer_(nullptr) {
    if (other.capacity_ != 0) {
      buffer_ = new T[other.capacity_];
      try {
        for (size_t i = 0; i < other.size_; ++i) {
          buffer_[i] = other.buffer_[i];
        }
      } catch (...) {
        delete[] buffer_;
        capacity_ = 0;
        size_ = 0;
        buffer_ = nullptr;
        throw;
      }
    }
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      Vector<T>(std::move(other)).Swap(*this);
    }
    return *this;
  }

  Vector &operator=(const Vector &other) {
    if (&other != this) {
      Vector<T>(other).Swap(*this);
    }
    return *this;
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return 0 == size_;
  }

  T &operator[](const size_t &id) {
    return buffer_[id];
  }

  const T &operator[](const size_t &id) const {
    return buffer_[id];
  }

  T &At(const size_t &id) {
    if (id >= size_) {
      throw std::out_of_range("out of range");
    }
    return buffer_[id];
  }

  const T &At(const size_t &id) const {
    if (id >= size_) {
      throw std::out_of_range("out of range");
    }
    return buffer_[id];
  }

  T &Front() {
    return At(0);
  }

  const T &Front() const {
    return At(0);
  }

  T &Back() {
    return At(size_ - 1);
  }

  const T &Back() const {
    return At(size_ - 1);
  }

  T *Data() {
    return buffer_;
  }

  const T *Data() const {
    return buffer_;
  }

  void Swap(Vector &other) {
    std::swap(other.capacity_, capacity_);
    std::swap(other.size_, size_);
    std::swap(other.buffer_, buffer_);
  }

  void Resize(const size_t &new_size) {
    Reserve(new_size);
    size_ = new_size;
  }

  void Resize(const size_t &new_size, const T &value) {
    if (new_size > capacity_) {
      auto tmp = new T[new_size];
      try {
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move_if_noexcept(buffer_[i]);
        }
        for (size_t i = size_; i < new_size; ++i) {
          tmp[i] = value;
        }
      } catch (...) {
        delete[] tmp;
        throw;
      }
      delete[] buffer_;
      buffer_ = tmp;
      capacity_ = new_size;
      size_ = new_size;
    } else {
      for (size_t i = size_; i < new_size; ++i) {
        buffer_[i] = value;
      }
      size_ = new_size;
    }
  }

  void Reserve(const size_t &capacity) {
    if (capacity > capacity_) {
      auto tmp = new T[capacity];
      try {
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move_if_noexcept(buffer_[i]);
        }
      } catch (...) {
        delete[] tmp;
        throw;
      }
      delete[] buffer_;
      capacity_ = capacity;
      buffer_ = tmp;
    }
  }

  void ShrinkToFit() {
    T *tmp = nullptr;
    if (size_ > 0) {
      tmp = new T[size_];
      try {
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move_if_noexcept(buffer_[i]);
        }
      } catch (...) {
        delete[] tmp;
        throw;
      }
    }
    delete[] buffer_;
    buffer_ = tmp;
    capacity_ = size_;
  }

  void Clear() {
    size_ = 0;
  }

  void PushBack(const T &value) {
    if (size_ == capacity_) {
      auto new_cap = 2 * capacity_;
      if (capacity_ == 0) {
        new_cap = 1;
      }
      auto tmp = new T[new_cap];
      try {
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move_if_noexcept(buffer_[i]);
        }
        tmp[size_] = value;
      } catch (...) {
        delete[] tmp;
        throw;
      }
      delete[] buffer_;
      buffer_ = tmp;
      capacity_ = new_cap;
      ++size_;
    } else {
      buffer_[size_] = value;
      ++size_;
    }
  }

  void PushBack(T &&value) {
    if (size_ == capacity_) {
      auto new_cap = 2 * capacity_;
      if (capacity_ == 0) {
        new_cap = 1;
      }
      auto tmp = new T[new_cap];
      try {
        for (size_t i = 0; i < size_; ++i) {
          tmp[i] = std::move_if_noexcept(buffer_[i]);
        }
        tmp[size_] = std::move(value);
      } catch (...) {
        delete[] tmp;
        throw;
      }
      delete[] buffer_;
      buffer_ = tmp;
      capacity_ = new_cap;
      ++size_;
    } else {
      buffer_[size_] = std::move(value);
      ++size_;
    }
  }

  void PopBack() {
    if (size_ > 0) {
      --size_;
    }
  }

  bool operator<(const Vector &other) const {
    size_t min_size = std::min(size_, other.size_);
    for (size_t i = 0; i < min_size; ++i) {
      if (buffer_[i] < other.buffer_[i]) {
        return true;
      }
      if (buffer_[i] > other.buffer_[i]) {
        return false;
      }
    }
    return size_ < other.size_;
  }

  bool operator>(const Vector &other) const {
    size_t min_size = std::min(size_, other.size_);
    for (size_t i = 0; i < min_size; ++i) {
      if (buffer_[i] > other.buffer_[i]) {
        return true;
      }
      if (buffer_[i] < other.buffer_[i]) {
        return false;
      }
    }
    return other.size_ < size_;
  }

  bool operator<=(const Vector &other) const {
    return *this < other || other == *this;
  }

  bool operator>=(const Vector &other) const {
    return *this == other || other < *this;
  }

  bool operator!=(const Vector &other) const {
    return *this < other || other < *this;
  }

  bool operator==(const Vector &other) const {
    return !(*this < other || other < *this);
  }

  Iterator begin() {  // NOLINT
    return buffer_;
  }

  ConstIterator begin() const {  // NOLINT
    return buffer_;
  }

  Iterator end() {  // NOLINT
    return &(buffer_[size_]);
  }

  ConstIterator end() const {  // NOLINT
    return &(buffer_[size_]);
  }

  ConstIterator cbegin() const {  // NOLINT
    return buffer_;
  }

  ConstIterator cend() const {  // NOLINT
    return &(buffer_[size_]);
  }

  ReverseIterator rbegin() {  // NOLINT
    return ReverseIterator(end());
  }

  ReverseIterator rend() {  // NOLINT
    return ReverseIterator(begin());
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return ConstReverseIterator(end());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return ConstReverseIterator(begin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return ConstReverseIterator(end());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return ConstReverseIterator(begin());
  }

  ~Vector() {
    delete[] buffer_;
  }
};