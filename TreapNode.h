#pragma once

#include <random>
#include "BSNode.h"

template <class T>
class TreapNode : public BSNode<T>
{
  typedef unsigned long long ull;
  
public:
  using BSNode<T>::value;
  using BSNode<T>::parent;
  using BSNode<T>::left;
  using BSNode<T>::right;
  using BSNode<T>::size;
  using BSNode<T>::my_ord;
  using BSNode<T>::update_size;
  
  TreapNode(T v) : BSNode<T>(v)
  {
    ull msb = rand()%MOD, lsb = rand()%MOD;
    priority = msb*MOD + lsb;
  }
  
  // Modifiers
  virtual TreapNode* insert(const T& v) override;
  virtual TreapNode* remove(const T& v) override;
  
  virtual TreapNode*  rotate_left() override; 
  virtual TreapNode* rotate_right() override;

  virtual void print(int op=0);
  
private:
  static const ull MOD{100};//MOD{1000000007};
  ull priority;

  void heapify();
};


template <class T>
TreapNode<T>* TreapNode<T>::insert(const T& v)
{
  if(value == v)
    return this;

  BSNode<T>* &sub_t = (v < value)? left : right;
  TreapNode<T>* t;

  if(!sub_t)
    {
      sub_t = new TreapNode<T>(v);
      sub_t->parent = this;
      t = (TreapNode<T>*)sub_t;
      t->heapify();    
    }
  else
    t = (TreapNode<T>*)sub_t->insert(v);

  update_size();

  return t;
}


template <class T>
TreapNode<T>* TreapNode<T>::remove(const T& v)
{
  typedef TreapNode<T>* TNT;

  TNT t = (TNT)BSNode<T>::insert(v);
  while(t->left || t->right)
    {
      if(t->left && (!t->right || ((TNT)t->left)->priority > ((TNT)t->right)->priority))
	t->rotate_right();
      else
	t->rotate_left();
    }

  BSNode<T>* p = this;
  while(p->parent)
    p = p->parent;

  return (TNT)p->BSNode<T>::remove(v);
}


template <class T>
TreapNode<T>* TreapNode<T>::rotate_left()
{
  return (TreapNode*) BSNode<T>::rotate_left();
}


template <class T>
TreapNode<T>* TreapNode<T>::rotate_right()
{
  return (TreapNode*) BSNode<T>::rotate_right();
}


template<class T>
void TreapNode<T>::print(int op)
{
  if(op == 0)
    {
      int left_spaces = my_ord();
  
      for(int i=0; i<left_spaces; i++)
	printf("     ");
      std::cout << "(" << value << "," << priority << ")" << std::endl;

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
      std::cout << "(" << value << "," << priority << ")";
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
void TreapNode<T>::heapify()
{
  if(parent && ((TreapNode<T>*)parent)->priority < priority)
    {
      if(parent->left == this)
	parent->rotate_right();
      else
	parent->rotate_left();
      heapify();
    }
}
