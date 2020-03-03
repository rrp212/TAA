#pragma once

#include <cassert>
#include "Set.h"

template <class T>
class BinTree : public Set<T>
{
protected:
  T value;
  BinTree* parent{nullptr};
  BinTree*   left{nullptr};
  BinTree*  right{nullptr};
  unsigned int m_size{0};     //including self

  BinTree* rotate_left(); 
  BinTree* rotate_right();

public:
  BinTree() = default;
  
  BinTree(T v): value(v)
  {
  }

  BinTree(BinTree* p): parent(p)
  {
  }

  ~BinTree()
  {
    delete(left);
    delete(right);
  }

  // Capacity
  virtual bool        empty();
  virtual unsigned int size();

  // Modifiers
  virtual void            clear();
  virtual void insert(const T& v);
  virtual void remove(const T& v);

  // Lookup
  virtual unsigned int            count(const T& v);
  virtual const T&          lower_bound(const T& v);
  virtual const T&          upper_bound(const T& v);
  virtual bool range_search(const T& l, const T& r);
  virtual const T&                            min();
  virtual const T&                            max();
};


template <class T>
BinTree<T>* BinTree<T>::rotate_left() // TODO <<<<<<<<<<<<<<<<<<<<
{
  return this;
}


template <class T>
BinTree<T>* BinTree<T>::rotate_right()  // TODO <<<<<<<<<<<<<<<<<<
{
  return this;
}


template <class T>
bool BinTree<T>::empty()
{
  return m_size == 0;
}


template <class T>
unsigned int BinTree<T>::size()
{
  return m_size;
}


template <class T>
void BinTree<T>::clear()
{
  delete(left);
  delete(right);

  parent = nullptr;
  left = nullptr;
  right = nullptr;
  m_size = 0;
}


template <class T>
void BinTree<T>::insert(const T& v)
{
  if(m_size == 0)
    value = v;
  else if(value == v)
    return;
  else
    {
      BinTree<T>* sub_t = (v < value)? left : right;
      if(!sub_t)
	sub_t = new BinTree<T>(this);
      sub_t->insert(v);
    }
  
  m_size++;
}


template <class T>
void BinTree<T>::remove(const T& v)
{
  if(m_size == 0)
    return;

  if(value == v)
    {
      if(left && right)
	{
	  value = left->max();
	  left->remove(value);
	}
      else
	{
	  BinTree<T>* sub_t = left? left : right;

	  if(parent->left == this)
	    parent->left = sub_t;
	  else
	    parent->right = sub_t;

	  if(sub_t)
	    sub_t->parent = parent;

	  left  = nullptr;
	  right = nullptr;
	  delete(this);
	  return;
	}
    }
  else
    {
      BinTree<T>* sub_t = (v < value)? left : right;
      sub_t->remove(v);
    }

  m_size--;
}


template <class T>
unsigned int BinTree<T>::count(const T& v)
{
  if(m_size == 0)
    return 0;

  if(value == v)
    return 1;

  BinTree<T>* sub_t = (v < value)? left : right;
  return sub_t->count(v);
}


template <class T>
const T& BinTree<T>::lower_bound(const T& v)
{
  return v;
}


template <class T>
const T& BinTree<T>::upper_bound(const T& v)
{
  return v;
}


template <class T>
bool BinTree<T>::range_search(const T& l, const T& r)
{
  return true;
}


template <class T>
const T& BinTree<T>::min()
{
  BinTree<T>* t = this;
  while(t->left)
    t = t->left;
  return t->value;
}


template <class T>
const T& BinTree<T>::max()
{
  BinTree<T>* t = this;
  while(t->right)
    t = t->right;
  return t->value;
}
