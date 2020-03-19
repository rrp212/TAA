#pragma once

#include "BSNode.h"

template <class T>
class SplayNode : public BSNode<T>
{
public:
  using BSNode<T>::value;
  using BSNode<T>::parent;
  using BSNode<T>::left;
  using BSNode<T>::right;
  using BSNode<T>::update_size;
  
  SplayNode(T v): BSNode<T>(v)
  {
  }

  // Modifiers
  virtual SplayNode* insert(const T& v) override;
  virtual SplayNode* remove(const T& v) override;

  virtual SplayNode*  rotate_left() override; 
  virtual SplayNode* rotate_right() override;

  // Lookup
  virtual bool count(const T& v) override;

private:
  void splay();
};


template <class T>
SplayNode<T>* SplayNode<T>::insert(const T& v)
{
  if(value == v)
    {
      splay();
      return this;
    }
  
  BSNode<T>* &sub_t = (v < value)? left : right;
  SplayNode<T>* t;

  if(!sub_t)
    {
      sub_t = new SplayNode<T>(v);
      sub_t->parent = this;
      t = (SplayNode<T>*) sub_t;
      t->splay();
    }
  else
    t = (SplayNode<T>*) sub_t->insert(v);

  update_size();

  return t;
}


template <class T>
SplayNode<T>* SplayNode<T>::remove(const T& v)
{
  SplayNode<T>* t = SplayNode<T>::insert(v);
  return (SplayNode*) t->BSNode<T>::remove(v);
}


template <class T>
SplayNode<T>* SplayNode<T>::rotate_left()
{
  return (SplayNode<T>*) BSNode<T>::rotate_left();
}


template <class T>
SplayNode<T>* SplayNode<T>::rotate_right()
{
  return (SplayNode<T>*) BSNode<T>::rotate_right();
}


template <class T>
bool SplayNode<T>::count(const T& v)
{
  if(value == v)
    {
      splay();
      return 1;
    }
  
  BSNode<T>* sub_t = (v < value)? left : right;
  return sub_t? sub_t->count(v) : 0;
}


template <class T>
void SplayNode<T>::splay()
{
  while (parent)
    {
      if (!parent->parent)
	{
	  if (parent->left == this)
	    parent->rotate_right();
	  else
	    parent->rotate_left();
	}
      else
	{
	  if (parent->left == this && parent->parent->left == parent)
	    {
	      parent->parent->rotate_right();
	      parent->rotate_right();
	    }
	  else if (parent->right == this && parent->parent->right == parent)
	    {
	      parent->parent->rotate_left();
	      parent->rotate_left();
	    }
	  else if (parent->left == this && parent->parent->right == parent)
	    {
	      parent->rotate_right();
	      parent->rotate_left();
	    }
	  else
	    {
	      parent->rotate_left();
	      parent->rotate_right();
	    }
	}
    }
}
