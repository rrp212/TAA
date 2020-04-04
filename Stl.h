#pragma once

#include <iostream>
#include <set>
#include <utility>
#include "Set.h"


template <class T>
class Stl : public Set<T>
{
private:
  std::set<T> S;
  
public:
  // Capacity
  virtual bool        empty();
  virtual unsigned int size();

  // Modifiers
  virtual Stl<T>&            clear();
  virtual Stl<T>& insert(const T& v);
  virtual Stl<T>& remove(const T& v);

  // Lookup
  virtual bool                            count(const T& v);
  virtual std::pair<const T&, bool> lower_bound(const T& v);
  virtual std::pair<const T&, bool> upper_bound(const T& v);
  virtual bool         range_search(const T& l, const T& r);
  virtual std::pair<const T&, bool>                   min();
  virtual std::pair<const T&, bool>                   max();

  virtual void print(int op=0);
};


template <class T>
bool Stl<T>::empty()
{
  return S.empty();
}


template <class T>
unsigned int Stl<T>::size()
{
  return S.size();
}

template <class T>
Stl<T>& Stl<T>::clear()
{
  S.clear();
  return *this;
}


template <class T>
Stl<T>& Stl<T>::insert(const T& v)
{
  S.insert(v);
  return *this;
}


template <class T>
Stl<T>& Stl<T>::remove(const T& v)
{
  S.erase(v);
  return *this;
}


template <class T>
bool Stl<T>::count(const T& v)
{
  return S.count(v);
}


template <class T>
std::pair<const T&, bool> Stl<T>::lower_bound(const T& v) // first >=v
{
  auto it = S.lower_bound(v);
  if(it!=S.end())
    return std::make_pair(*it,true);
  return std::make_pair(v, false);
}


template <class T>
std::pair<const T&, bool> Stl<T>::upper_bound(const T& v) // first >v
{
  auto it = S.upper_bound(v);
  if(it!=S.end())
    return std::make_pair(*it,true);
  return std::make_pair(v, false);
}


template <class T>
bool Stl<T>::range_search(const T& l, const T& r)
{
  auto it = S.lower_bound(l);
  return it!=S.end() && *it<=r;
}


template <class T>
std::pair<const T&, bool> Stl<T>::min()
{
  if(!S.empty())
    return std::make_pair(*S.begin(), true);
  T x;
  return std::make_pair(x, false);
}


template <class T>
std::pair<const T&, bool> Stl<T>::max()
{
  if(!S.empty())
    return std::make_pair(*S.rbegin(), true);
  T x;
  return std::make_pair(x, false);
}


template <class T>
void Stl<T>::print(int op)
{
  std::cout << "Size: " << S.size() << std::endl;
  for (auto it=S.begin(); it!=S.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << std::endl;
}
