#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

class String {
private:
  char* arr = new char[15];
  size_t sz = 0;
  size_t cap = 15;
  
  explicit String(size_t n);

  void ensure_capacity(size_t new_cap);

public:
  String();

  String(char c);
  
  String(size_t n, char c);
  
  String(const char* str);
  
  String(std::initializer_list<char> list);
  
  String(const String& other);

  String(std::string str);
  
  String& operator=(String other) &;
  
  void swap(String& other);

  ~String();

  size_t size() const;

  size_t length() const;

  size_t capacity() const;

  bool empty() const;

  void clear();

  String& erase(size_t pos, size_t count = std::string::npos);

  char& at(size_t index); 

  const char& at(size_t index) const;

  char& front();

  const char& front() const;

  char& back();

  const char& back() const;

  void push_back(char c);

  void pop_back();

  String& append(const String& other);

  String& append(const char* str);

  String& append(char c);

  String& insert(size_t pos, const String& str);
  
  String& insert(size_t pos, const char* str);
  
  String& insert(size_t pos, size_t count, char c);

  String& replace(size_t pos, size_t count, const String& str);
  
  String& replace(size_t pos, size_t count, const char* str);
  
  String& replace(size_t pos, size_t count, size_t n, char c);

  size_t find(const String& str, size_t pos = 0) const;

  size_t find(const char* str, size_t pos = 0) const;

  size_t find(char c, size_t pos = 0) const;

  void resize (size_t n);

  void resize (size_t n, char c);

  String substr (size_t pos = 0, size_t len = std::string::npos) const;

  char& operator[](size_t index);

  const char& operator[](size_t index) const;

  bool operator==(const char* str);

  bool operator==(const String& other);

  bool operator==(const char c);

  String& operator+=(const String& other); 

  String& operator+=(const char* str);

  String& operator+=(const char c);

  String operator+(const char lhs) const; 

  String operator+(const char* other) const;

  String operator+(const String& other) const;

  friend String operator+(char lhs, const String& rhs); 

  friend String operator+(const char* lhs, const String& rhs);

  friend std::ostream& operator<<(std::ostream& os, const String& str);
  
  std::weak_ordering operator<=>(String other);

  std::weak_ordering operator<=>(const char* other);

  std::weak_ordering operator<=>(std::string other);
};

String operator+(char lhs, const String& rhs);

String operator+(const char* lhs, const String& rhs);

#endif // STRING_H 
