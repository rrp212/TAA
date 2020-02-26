#pragma once

#include <stdio.h>

template<struct T>
struct AVLNode {
  T value;
  int height;
  AVLNode<T>* parent, left, right;

  AVLNode(T v=NULL, AVLNode* p=NULL)
  {
    value = v;
    height = 1;
    parent = p;
    left = right = NULL;
  }

  ~AVLNode()
  {
    delete(left);
    delete(right);
  }

  AVLNode<T>* find(T v)
  {
    if(value == v)
      return this;
    else if(value < v)
      return left? left.find(v) : NULL;
    else
      return right? right.find(v) : NULL;
  }

  void insert(T v)
  {
    if(v < value)   // Insert left
      {
	if(left)
	  left.insert(v);
	else
	  left = new AVLNode<T>(v, this);
      }
    else            // Insert Right
      {
	if(right)
	  right.insert(v);
	else
	  right = new AVLNode<T>(v, this);
      }
  }

  void remove(T v)
  {
    if(v < value && left)
      return left.remove(v);
    else if(value < v && right)
      return right.remove(v);
    else if(value != v)
      return;

    // CONTINUE HERE
  }

  T get_min()
  {
    return left==NULL? value : left.get_min();
  }
  
  T get_max()
  {
    return right==NULL? value : right.get_max();
  }
};  
