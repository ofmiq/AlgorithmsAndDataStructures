#include "String.h"

void String::ensure_capacity(size_t new_cap) {
  if (new_cap <= cap) return; 
  cap = std::max(new_cap + 1, cap * 2);
  char* new_arr = new char[cap];
  std::copy(arr, arr + sz, new_arr);
  new_arr[sz] = '\0';
  delete[] arr;
  arr = new_arr;
}

String::String() = default;

String::String(char c): arr(new char[15]), sz(1), cap(15) {
  arr[0] = c;
  arr[sz] = '\0';
}

String::String(size_t n, char c) {
  ensure_capacity(n);
  sz = n;
  std::fill(arr, arr + sz, c);
  arr[sz] = '\0';
}

String::String(const char* str) {
  ensure_capacity(strlen(str));
  sz = strlen(str);
  std::copy(str, str + sz, arr);
  arr[sz] = '\0';
}

String::String(std::initializer_list<char> list) {
  ensure_capacity(list.size());
  sz = list.size();
  std::copy(list.begin(), list.end(), arr);
  arr[sz] = '\0';
}

String::String(const String& other) {
  ensure_capacity(other.size());
  sz = other.size();
  std::copy(other.arr, other.arr + sz, arr);
  arr[sz] = '\0';
}

String::String(std::string str) {
  ensure_capacity(str.size());
  sz = str.size();
  std::copy(str.begin(), str.end(), arr);
  arr[sz] = '\0';
}

String& String::operator=(String other) & {
  swap(other);
  return *this;
}

void String::swap(String& other) {
  std::swap(arr, other.arr);
  std::swap(sz, other.sz);
  std::swap(cap, other.cap);
}

String::~String() {
  delete[] arr;
}

size_t String::size() const {
  return sz;
}

size_t String::length() const {
  return sz;
}

size_t String::capacity() const {
  return cap;
}

bool String::empty() const {
  return sz == 0;
}

void String::clear() {
  sz = 0;
  arr[sz] = '\0';
}

String& String::erase(size_t pos, size_t count) {
  if (pos >= sz) return *this;
  size_t eraseCount = std::min(count, sz - pos);
  std::copy(arr + pos + eraseCount, arr + sz, arr + pos);
  sz = sz - eraseCount;
  arr[sz] = '\0';
  return *this;
}

char& String::at(size_t index) {
  if (index >= sz) {
    throw std::out_of_range("Index out of range");
  }
  return arr[index];
}

const char& String::at(size_t index) const {
  if (index >= sz) {
    throw std::out_of_range("Index out of range");
  }
  return arr[index];
}

char& String::front() {
  if (sz == 0) {
    throw std::out_of_range("String is empty");
  }
  return arr[0];
}

const char& String::front() const {
  if (sz == 0) {
    throw std::out_of_range("String is empty");
  }
  return arr[0];
}

char& String::back() {
  if (sz == 0) {
    throw std::out_of_range("String is empty");
  }
  return arr[sz - 1];
}

const char& String::back() const {
  if (sz == 0) {
    throw std::out_of_range("String is empty");
  }
  return arr[sz - 1];
}

void String::push_back(char c) {
  ensure_capacity(sz + 1);
  arr[sz++] = c;
  arr[sz] = '\0';
}

void String::pop_back() {
  if (sz == 0) return;
  --sz;
  arr[sz] = '\0';
}

String& String::append(const String& other) {
  ensure_capacity(sz + other.sz);
  std::copy(other.arr, other.arr + other.sz, arr + sz);
  sz += other.sz;
  arr[sz] = '\0';
  return *this;
}

String& String::append(const char* str) {
  size_t str_len = strlen(str);
  ensure_capacity(sz + str_len);
  std::copy(str, str + str_len, arr + sz);
  sz += str_len;
  arr[sz] = '\0';
  return *this;
}

String& String::append(char c) {
  push_back(c);
  return *this;
}


String& String::insert(size_t pos, const String& str) {
  if (pos > sz) {
    throw std::out_of_range("Index out of range");
  }

  size_t newSize = sz + str.sz;
  ensure_capacity(newSize);
  std::copy_backward(arr + pos, arr + sz, arr + newSize);
  std::copy(str.arr, str.arr + str.sz, arr + pos);
  sz = newSize;
  arr[sz] = '\0';
  return *this;
}

String& String::insert(size_t pos, const char* str) {
  if (pos > sz) {
    throw std::out_of_range("Index out of range");
  }

  size_t strLen = strlen(str);
  size_t newSize = sz + strLen;
  ensure_capacity(newSize);
  std::copy_backward(arr + pos, arr + sz, arr + newSize);
  std::copy(str, str + strLen, arr + pos);
  sz = newSize;
  arr[sz] = '\0';
  return *this;
}

String& String::insert(size_t pos, size_t count, char c) {
  if (pos > sz) {
    throw std::out_of_range("Index out of range");
  }

  size_t newSize = sz + count;
  ensure_capacity(newSize);
  std::copy_backward(arr + pos, arr + sz, arr + newSize);
  std::fill(arr + pos, arr + pos + count, c);
  sz = newSize;
  arr[sz] = '\0';
  return *this;
}

String& String::replace(size_t pos, size_t count, const String& str) {
  if (pos > sz) {
      throw std::out_of_range("String::replace");
  }
  count = std::min(count, sz - pos);
  size_t newSize = sz - count + str.sz;
  ensure_capacity(newSize);
  std::copy_backward(arr + pos + count, arr + sz, arr + newSize);
  std::copy(str.arr, str.arr + str.sz, arr + pos);
  sz = newSize;
  arr[sz] = '\0';
  return *this;
}

String& String::replace(size_t pos, size_t count, const char* str) {
  return replace(pos, count, String(str));
}

String& String::replace(size_t pos, size_t count, size_t n, char c) {
  if (pos > sz) {
      throw std::out_of_range("String::replace");
  }
  count = std::min(count, sz - pos);
  size_t newSize = sz - count + n;
  ensure_capacity(newSize);
  std::copy_backward(arr + pos + count, arr + sz, arr + newSize);
  std::fill_n(arr + pos, n, c);
  sz = newSize;
  arr[sz] = '\0';
  return *this;
}

void String::resize(size_t n) {
  if (n < sz) {
    sz = n;
    arr[sz] = '\0';
  } else {
    ensure_capacity(n);
    while (sz < n) {
      arr[sz++] = '\0';
    }
  }
}

void String::resize(size_t n, char c) {
  if (n < sz) {
    sz = n;
    arr[sz] = '\0';
  } else {
    ensure_capacity(n);
    while (sz < n) {
      arr[sz++] = c;
    }
    arr[sz] = '\0';
  }
}


size_t String::find(const String& str, size_t pos) const {
  if (pos >= sz) {
    return std::string::npos;
  }

  const char* found = std::search(arr + pos, arr + sz, str.arr, str.arr + str.sz);

  if (found == arr + sz) {
    return std::string::npos;
  } 

  return found - arr;
}


size_t String::find(const char* s, size_t pos) const {
  if (pos >= sz) {
    return std::string::npos;
  }
  
  const char* found = std::strstr(arr + pos, s);
  if (found == nullptr) {
    return std::string::npos;
  }
  
  return found - arr;
}

size_t String::find(char c, size_t pos) const {
  if (pos >= sz) {
    return std::string::npos;
  }
  
  const char* found = std::find(arr + pos, arr + sz, c);
  if (found == arr + sz) {
    return std::string::npos;
  }

  return found - arr;
}

String String::substr(size_t pos, size_t len) const {
  if (pos >= sz) {
    throw std::out_of_range("Index out of range");
  }

  if (len == std::string::npos || pos + len > sz) {
    len = sz - pos;
  }

  String sub;

  if (len == 0) return sub;

  sub.ensure_capacity(len);
  std::copy(arr + pos, arr + pos + len, sub.arr);
  sub.sz = len;
  sub.arr[len] = '\0';

  return sub;
}

char& String::operator[](size_t index) {
  return at(index);
}

const char& String::operator[](size_t index) const {
  return at(index);
}

bool String::operator==(const char* c) {
  size_t len = strlen(c);
  if (sz != len) {
    return false;
  }
  for (size_t i = 0; i < sz; ++i) {
    if (arr[i] != c[i]) {
      return false;
    }
  }
  return true;
}

bool String::operator==(const String& other) {
  if (sz != other.sz) {
    return false;
  }
  for (size_t i = 0; i < sz; ++i) {
    if (arr[i] != other.arr[i]) {
      return false;
    }
  }
  return true;
}

bool String::operator==(const char c) {
  if (sz != 1) {
    return false;
  }
  return arr[0] == c;
}

String String::operator+(const char lhs) const {
  String result(*this);
  result.push_back(lhs);
  return result;
}

String String::operator+(const char* other) const {
  String result(*this);
  size_t other_length = strlen(other);
  result.ensure_capacity(result.sz + other_length);
  std::copy(other, other + other_length, result.arr + result.sz);
  result.sz += other_length;
  result.arr[result.sz] = '\0';
  return result;
}

String String::operator+(const String& other) const {
  String result(*this);
  result.append(other);
  return result;
}

String operator+(char lhs, const String& rhs) {
  String result(lhs);
  result += rhs;
  return result;
}

String operator+(const char* lhs, const String& rhs) {
  String result(lhs);
  result += rhs;
  return result;
}

String& String::operator+=(const String& other) {
  append(other);
  return *this;
}

String& String::operator+=(const char* str) {
  append(str);
  return *this; 
}

String& String::operator+=(const char c) {
  push_back(c);
  return *this;  
}

std::ostream& operator<<(std::ostream& os, const String& str) {
  return os << str.arr;
}

std::weak_ordering String::operator<=>(String other) {
  return strcmp(arr, other.arr) <=> 0;
}

std::weak_ordering String::operator<=>(const char* other) {
  return strcmp(arr, other) <=> 0;
}

std::weak_ordering String::operator<=>(std::string other) {
  return std::string(arr) <=> other;
}
