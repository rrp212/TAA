#pragma once

#include "Set.h"

template <class T, class N>
class Tree : public Set<T>
{
public:             // change to private after testing
  N* root{nullptr};

public:
  Tree() = default;

  ~Tree() { delete(root); }
  
  // Capacity
  virtual bool        empty();
  virtual unsigned int size();

  // Modifiers
  virtual Tree<T, N>&            clear();
  virtual Tree<T, N>& insert(const T& v);
  virtual Tree<T, N>& remove(const T& v);

  // Lookup
  virtual bool                            count(const T& v);
  virtual std::pair<const T&, bool> lower_bound(const T& v);
  virtual std::pair<const T&, bool> upper_bound(const T& v);
  virtual bool         range_search(const T& l, const T& r);
  virtual std::pair<const T&, bool>                   min();
  virtual std::pair<const T&, bool>                   max();

  virtual void print(int op=0);
};


template <class T, class N>
bool Tree<T, N>::empty()
{
  return root == nullptr;
}


template <class T, class N>
unsigned int Tree<T, N>::size()
{
  return root ? root->size : 0;
}


template <class T, class N>
Tree<T, N>& Tree<T, N>::clear()
{
  delete(root);
  root = nullptr;
  return *this;
}


template <class T, class N>
Tree<T, N>& Tree<T, N>::insert(const T& v)
{
  root ? root->insert(v) : root = new N(v);
  while(root->parent)
    root = (N*)root->parent;
  return *this;
}


template <class T, class N>
Tree<T, N>& Tree<T, N>::remove(const T& v)
{
  if(root)
    {
      if(root->size == 1 && root->value == v)
	clear();
      else {
	root = (N*)root->remove(v);
	while(root->parent)
	  root = (N*)root->parent;
      }
    }
  return *this;
}


template <class T, class N>
bool Tree<T, N>::count(const T& v)
{
  bool r = root ? root->count(v) : 0;
  while(root->parent)
    root = (N*)root->parent;
  return r;
}


template <class T, class N>
std::pair<const T&, bool> Tree<T, N>::lower_bound(const T& v) // first >=v
{
  if(!root)
    return std::make_pair(v, false);

  T x = root->lower_bound(v);
  return std::make_pair(x, x >= v);
}


template <class T, class N>
std::pair<const T&, bool> Tree<T, N>::upper_bound(const T& v) // first >v
{
  if(!root)
    return std::make_pair(v, false);

  T x = root->upper_bound(v);
  return std::make_pair(x, x > v);
}


template <class T, class N>
bool Tree<T, N>::range_search(const T& l, const T& r)
{
  return root ? root->range_search(l, r) : false;
}


template <class T, class N>
std::pair<const T&, bool> Tree<T, N>::min()
{
  T x;
  return root ? std::make_pair(root->min(), true) : std::make_pair(x, false);
}


template <class T, class N>
std::pair<const T&, bool> Tree<T, N>::max()
{
  T x;
  return root ? std::make_pair(root->max(), true) : std::make_pair(x, false);
}


template <class T, class N>
void Tree<T, N>::print(int op)
{
  printf("\n---vvv---\n");
  if(!root)
    printf("NULL\n");
  else
    root->print(op);
  printf("---^^^---\n\n");
}
