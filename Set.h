#pragma once

#include <utility>

template <class T>
class Set
{
public:
  // Capacity
  virtual bool        empty() = 0;
  virtual unsigned int size() = 0;

  // Modifiers
  virtual void               clear() = 0;
  virtual Set<T>* insert(const T& v) = 0;
  virtual Set<T>* remove(const T& v) = 0;

  // Lookup
  virtual bool                            count(const T& v) = 0;
  virtual std::pair<const T&, bool> lower_bound(const T& v) = 0;
  virtual std::pair<const T&, bool> upper_bound(const T& v) = 0;
  virtual bool         range_search(const T& l, const T& r) = 0;
  virtual std::pair<const T&, bool>                   min() = 0;
  virtual std::pair<const T&, bool>                   max() = 0;

  virtual void print(int op=0) = 0;
};
