#pragma once
#include <cstring>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  size_t size_;
  size_t capacity_;
  char *str_;

 public:
  String();
  String(size_t size, char symbol);
  String(const char *str);  // NOLINT
  String(const char *str, size_t size);
  String(const String &other);
  ~String();

  void Reserve(size_t new_capacity);
  void Resize(size_t new_size, char symbol);
  void ShrinkToFit();

  char &At(size_t id);
  char At(size_t) const;

  char &Front();
  char Front() const;
  char &Back();
  char Back() const;
  char *CStr() const;
  char *Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;

  void Clear();
  void Swap(String &other);

  void PopBack();
  void PushBack(char symbol);

  String &operator+=(const String &other);
  String &operator=(const String &other);
  char &operator[](size_t id);
  char operator[](size_t id) const;
  friend bool operator==(const String &first, const String &second);
  friend bool operator>(const String &first, const String &second);
  friend bool operator<(const String &first, const String &second);
  friend std::ostream &operator<<(std::ostream &os, const String &value);
};

String operator+(const String &first, const String &second);
bool operator!=(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator>=(const String &first, const String &second);