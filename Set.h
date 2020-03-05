#pragma once

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
  virtual void    remove(const T& v) = 0;

  // Lookup
  virtual unsigned int            count(const T& v) = 0;
  virtual const T&          lower_bound(const T& v) = 0;
  virtual const T&          upper_bound(const T& v) = 0;
  virtual bool range_search(const T& l, const T& r) = 0;
  virtual const T&                            min() = 0;
  virtual const T&                            max() = 0;

  virtual void print(int op=0) = 0;
};
