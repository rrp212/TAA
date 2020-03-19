#pragma once

#include <iostream>

template <class T>
class BSNode
{
public:
  T value;
  unsigned int size{1};
  
  BSNode* parent{nullptr};
  BSNode*   left{nullptr};
  BSNode*  right{nullptr};

  
  BSNode(T v): value(v)
  {
  }

  ~BSNode()
  {
    delete(left);
    delete(right);
  }

  // Modifiers
  virtual BSNode* insert(const T& v);
  virtual BSNode* remove(const T& v);

  virtual BSNode*  rotate_left(); 
  virtual BSNode* rotate_right();

  // Lookup
  virtual bool                    count(const T& v);
  virtual const T&          lower_bound(const T& v);
  virtual const T&          upper_bound(const T& v);
  virtual bool range_search(const T& l, const T& r);
  virtual const T&                            min();
  virtual const T&                            max();

  virtual void print(int op=0);

protected:
  unsigned int  my_ord();
  void     update_size();
};


template <class T>
BSNode<T>* BSNode<T>::insert(const T& v)
{
  if(value == v)
    return this;
  
  BSNode<T>* &sub_t = (v < value)? left : right;
  BSNode<T>* t;

  if(!sub_t)
    {
      sub_t = new BSNode<T>(v);
      sub_t->parent = this;
      t = sub_t;
    }
  else
    t = sub_t->insert(v);

  update_size();

  return t;
}


template <class T>
BSNode<T>* BSNode<T>::remove(const T& v)
{
  if(value == v)
    {
      if(left && right)
	{
	  value = left->max();
	  left->BSNode<T>::remove(value);
	}
      else
	{
	  BSNode<T>* sub_t = left? left : right;
	  
	  if(parent)
	    {
	      if(parent->left == this)
		parent->left = sub_t;
	      else
		parent->right = sub_t;
	    }
	  if(sub_t) 
	    sub_t->parent = parent;
	  
	  left  = nullptr;
	  right = nullptr;
	  delete(this);
	  return sub_t;
	}
    }
  else
    {
      BSNode<T>* sub_t = (v < value) ? left : right;
      
      if (sub_t)
	sub_t->remove(v);
    }
  
  update_size();
  return this;
}


/*
   P             P
   |      L      |
   A     -->     C     P,A,C,D change
  / \           / \
 B   C         A   E
    / \       / \
   D   E     B   D
*/
template <class T>
BSNode<T>* BSNode<T>::rotate_left()
{
  if(!right)
    return this;

  BSNode<T> *P=parent, *A=this, *C=right, *D=right->left;

  if(P == nullptr)
    C->parent = nullptr;
  else
    {
      (P->left == A)? P->left = C : P->right = C;
      C->parent = P;
    }

  C->left   = A;
  A->parent = C;

  A->right  = D;
  if(D)
    D->parent = A;

  A->update_size();
  C->update_size();

  return C;
}


/*
     P         P
     |    R    |
     A   -->   B     P,A,B,E change
    / \       / \
   B   C     D   A
  / \           / \
 D   E         E   C
*/
template <class T>
BSNode<T>* BSNode<T>::rotate_right()
{
  if(!left)
    return this;

  BSNode<T> *P=parent, *A=this, *B=left, *E=left->right;

  if(P == nullptr)
    B->parent = nullptr;
  else
    {
      (P->left == A)? P->left = B : P->right = B;
      B->parent = P;
    }

  B->right  = A;
  A->parent = B;

  A->left = E;
  if(E)
    E->parent = A;

  A->update_size();
  B->update_size();

  return B;
}


template <class T>
bool BSNode<T>::count(const T& v)
{
  if(value == v)
    return 1;

  BSNode<T>* sub_t = (v < value)? left : right;
  return sub_t? sub_t->count(v) : 0;
}


template <class T>
const T& BSNode<T>::lower_bound(const T& v) // first >=v
{
  return v;
}


template <class T>
const T& BSNode<T>::upper_bound(const T& v) // first >v
{ 
  return v;
}


template <class T>
bool BSNode<T>::range_search(const T& l, const T& r)
{
  return true;
}


template <class T>
const T& BSNode<T>::min()
{
  BSNode<T>* t = this;
  while(t->left)
    t = t->left;
  return t->value;
}


template <class T>
const T& BSNode<T>::max()
{
  BSNode<T>* t = this;
  while(t->right)
    t = t->right;
  return t->value;
}


template <class T>
void BSNode<T>::print(int op)
{ 
  if(op == 0)
    {
      int left_spaces = my_ord();
  
      for(int i=0; i<left_spaces; i++)
	printf("   ");
      std::cout << value << std::endl;

      if(left)
	left->print();
      if(right)
	right->print();
    }
  else if(op == 1)
    {
      if(left)
	left->print(1);

      printf("%d ", my_ord());
      std::cout << value;
      if(left)
	std::cout << " " << left->value;
      else
	printf(" NULL");
      if(parent)
	std::cout << " " << parent->value;
      else
	printf(" NULL");
      if(right)
	std::cout << " " << right->value;
      else
	printf(" NULL");
      printf(" %d\n", size);
      
      if(right)
	right->print(1);
    }
}


template <class T>
unsigned int BSNode<T>::my_ord()
{
  int ans = left? left->size : 0;
  BSNode<T>* t = this;
  while(t->parent)
    {
      if(t == t->parent->right)
	ans += t->parent->size - t->size;
      t = t->parent;
    }
  return ans;
}


template <class T>
void BSNode<T>::update_size()
{
  size = (left? left->size : 0) + (right? right->size : 0) + 1;
}
