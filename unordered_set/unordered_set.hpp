#pragma once
#include <iterator>
#include <list>
#include <vector>

template <class KeyT>
class UnorderedSet {
 private:
  size_t size_;
  size_t bucket_;
  std::vector<std::list<KeyT>> unordered_set_;

 public:
  UnorderedSet() : size_(0), bucket_(0), unordered_set_(std::vector<std::list<KeyT>>()) {
  }

  explicit UnorderedSet(const size_t &count)
      : size_(0), bucket_(count), unordered_set_(std::vector<std::list<KeyT>>(count)) {
  }

  template <class ForwardIterator>
  UnorderedSet(const ForwardIterator &begin, const ForwardIterator &end)
      : size_(0), bucket_(0), unordered_set_(std::vector<std::list<KeyT>>()) {
    for (auto iter = begin; iter != end; ++iter) {
      ++size_;
      ++bucket_;
      unordered_set_.emplace_back(std::list<KeyT>());
    }
    for (auto iter = begin; iter != end; ++iter) {
      auto id = std::hash<KeyT>{}(*iter) % bucket_;
      unordered_set_[id].push_back(*iter);
    }
  }

  UnorderedSet(const UnorderedSet<KeyT> &other)
      : size_(other.size_), bucket_(other.bucket_), unordered_set_(other.unordered_set_) {
  }

  UnorderedSet &operator=(const UnorderedSet<KeyT> &other) {
    if (&other != this) {
      size_ = other.size_;
      bucket_ = other.bucket_;
      unordered_set_ = other.unordered_set_;
    }
    return *this;
  }

  UnorderedSet(UnorderedSet<KeyT> &&other) noexcept
      : size_(other.size_), bucket_(other.bucket_), unordered_set_(other.unordered_set_) {
    other.size_ = 0;
    other.bucket_ = 0;
    other.unordered_set_.clear();
  }

  UnorderedSet &operator=(UnorderedSet<KeyT> &&other) noexcept {
    if (&other != this) {
      size_ = other.size_;
      bucket_ = other.bucket_;
      unordered_set_ = other.unordered_set_;
      other.size_ = 0;
      other.bucket_ = 0;
      other.unordered_set_.clear();
    }
    return *this;
  }

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void Clear() {
    size_ = 0;
  }

  void Insert(const KeyT &value) {
    if (bucket_ == 0) {
      Rehash(1);
    }
    unordered_set_[std::hash<KeyT>{}(value) % bucket_].push_back(value);
    ++size_;
    if (size_ > bucket_) {
      Rehash(2 * bucket_);
    }
  };

  void Insert(KeyT &&value) {
    if (bucket_ == 0) {
      Rehash(1);
    }
    unordered_set_[std::hash<KeyT>{}(value) % bucket_].push_back(value);
    size_++;
    if (size_ > bucket_) {
      Rehash(2 * bucket_);
    }
  }

  void Erase(const KeyT &x) {
    while (Find(x)) {
      unordered_set_[std::hash<KeyT>{}(x) % bucket_].remove(x);
      size_--;
    }
  }

  bool Find(const KeyT &value) const {
    if (bucket_ == 0 || size_ == 0) {
      return false;
    }
    for (const KeyT &iter : unordered_set_[std::hash<KeyT>{}(value) % bucket_]) {
      if (iter == value) {
        return true;
      }
    }
    return false;
  }

  void Rehash(const size_t &new_bucket_count) {
    if (new_bucket_count >= size_ && new_bucket_count != bucket_) {
      UnorderedSet<KeyT> tmp(new_bucket_count);
      for (size_t i = 0; i < bucket_; i++) {
        for (auto &iter : unordered_set_[i]) {
          tmp.Insert(iter);
        }
      }
      *this = tmp;
    }
  }

  void Reserve(const std::size_t &new_bucket_count) {
    if (new_bucket_count >= size_ && new_bucket_count > bucket_) {
      UnorderedSet<KeyT> tmp(new_bucket_count);
      for (size_t i = 0; i < bucket_; i++) {
        for (auto &iter : unordered_set_[i]) {
          tmp.Insert(iter);
        }
      }
      *this = tmp;
    }
  }

  const size_t &BucketCount() const {
    return bucket_;
  }

  size_t BucketSize(const size_t &id) const {
    if (id < bucket_) {
      return unordered_set_[id].sum();
    }
    return 0;
  }

  size_t Bucket(const KeyT &key) const {
    return std::hash<KeyT>{}(key) % bucket_;
  }

  double LoadFactor() const {
    if (bucket_ == 0) {
      return 0;
    }
    return static_cast<double>(size_) / (bucket_);
  }

  ~UnorderedSet() = default;
};