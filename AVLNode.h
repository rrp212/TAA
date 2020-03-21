#pragma once

#include <iostream>

template <class T>
class AVLNode : public BSNode<T>
{
public:
  using BSNode<T>::value;
  using BSNode<T>::parent;
  using BSNode<T>::left;
  using BSNode<T>::right;
  using BSNode<T>::size;
  using BSNode<T>::my_ord;
  using BSNode<T>::update_size;
  
  AVLNode(T v): BSNode<T>(v)
  {
  }

  // Modifiers
  virtual AVLNode* insert(const T& v) override;
  virtual AVLNode* remove(const T& v) override;

  virtual AVLNode*  rotate_left() override;
  virtual AVLNode* rotate_right() override;

  virtual void print(int op=0) override;
private:
  unsigned long long height = 1;
  void balance();
  void update_height();
};


template <class T>
AVLNode<T>* AVLNode<T>::insert(const T& v)
{
  if(value == v)
    return this;
  
  BSNode<T>* &sub_t = (v < value)? left : right;
  AVLNode<T>* t;

  if(!sub_t)
    {
      sub_t = new AVLNode<T>(v);
      sub_t->parent = this;
      t = (AVLNode<T>*) sub_t;
    }
  else
    t = (AVLNode<T>*) sub_t->insert(v);

  update_size();
  balance();
  
  return t;
}


template <class T>
AVLNode<T>* AVLNode<T>::remove(const T& v)
{
  if (v == value)
    {
      if(left && right)
	{
	  value = left->max();
	  left->remove(value);
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
	  return (AVLNode<T>*) sub_t;
	}
    }
  else
    {
      BSNode<T>* sub_t = (v < value) ? left : right;
      
      if (sub_t)
	sub_t->remove(v);
    }

  update_size();
  balance();

  return this;
}


template <class T>
AVLNode<T>* AVLNode<T>::rotate_left()
{
  return (AVLNode<T>*) BSNode<T>::rotate_left();
}


template <class T>
AVLNode<T>* AVLNode<T>::rotate_right()
{
  return (AVLNode<T>*) BSNode<T>::rotate_right();
}


template <class T>
void AVLNode<T>::print(int op)
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
      printf(" %d", size);
      printf(" %d\n", height);
      
      if(right)
	right->print(1);
    }
}


template <class T>
void AVLNode<T>::balance()
{
  long long left_height  = left? ((AVLNode<T>*) left)->height : 0,
            right_height = right? ((AVLNode<T>*) right)->height : 0;
  
  height = std::max(left_height, right_height) + 1;

  if (left_height - right_height > 1)
    {
      long long ll_height = left->left? ((AVLNode<T>*) left->left)->height : 0,
           	lr_height = left->right? ((AVLNode<T>*) left->right)->height : 0;
      if (lr_height - ll_height >= 1)
	{
	  left->rotate_left();
	  ((AVLNode<T>*) left->left)->update_height();
	}
      rotate_right();
    }
  if (right_height - left_height > 1)
    {
      long long rr_height = right->right? ((AVLNode<T>*) right->right)->height : 0,
	        rl_height = right->left? ((AVLNode<T>*) right->left)->height : 0;
      if (rl_height - rr_height >= 1)
	{
	  right->rotate_right();
	  ((AVLNode<T>*) right->right)->update_height();
	}
      rotate_left();
    }

  update_height();

  if (parent) ((AVLNode<T>*) parent)->update_height();
}

template<class T>
void AVLNode<T>::update_height()
{
  height = std::max(left? ((AVLNode<T>*) left)->height : 0,
		    right? ((AVLNode<T>*) right)->height : 0) + 1;
}
