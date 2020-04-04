#pragma once

#include <iostream>
#include <random>
#include <vector>
#include "Set.h"

template <class T>
class SkipNode
{
public:
  T value;
  unsigned int N;
  SkipNode<T>** next;

  SkipNode() = default;
    
  SkipNode(T v, int nLevels, double pLevel, SkipNode<T>* last): value(v)
  {
    N=1;
    while(N <= nLevels && rand()/(double)RAND_MAX < pLevel)
      N++;
    next = new SkipNode<T>*[N];
    for(int i=0;i<N;i++)
      next[i] = last;
  }

  ~SkipNode()
  {
  }
};

template <class T>
class SkipList : public Set<T>
{
private:
  const double pLevel{0.7};
  unsigned int nLevels{0};
  std::vector<SkipNode<T>*> header;
  SkipNode<T>* last;
  unsigned int m_size{0};
  
public:
  SkipList()
  {
    last = new SkipNode<T>();
    header.push_back(last);
  }

  ~SkipList()
  {
    clear();
    delete(last);
  }
  
  // Capacity
  virtual bool        empty();
  virtual unsigned int size();

  // Modifiers
  virtual SkipList<T>&            clear();
  virtual SkipList<T>& insert(const T& v);
  virtual SkipList<T>& remove(const T& v);

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
bool SkipList<T>::empty()
{
  return m_size==0;
}


template <class T>
unsigned int SkipList<T>::size()
{
  return m_size;
}


template <class T>
SkipList<T>& SkipList<T>::clear()
{
  SkipNode<T>* p;
  while(header[0] != last)
    {
      p = header[0]->next[0];
      delete(header[0]);
      header[0] = p;
    }
  nLevels = 0;
  header.clear();
  header.push_back(last);
  m_size = 0;
  return *this;
}


template <class T>
SkipList<T>& SkipList<T>::insert(const T& v)
{
  if(count(v))
    return *this;
  
  SkipNode<T>* no = new SkipNode<T>(v, nLevels, pLevel, last);
  while(nLevels < no->N)
    {
      header.push_back(last);
      nLevels++;
    }
  SkipNode<T>* p=nullptr;
  for(int i=nLevels-1;i>=0;i--)
    {
      if(!p)
	{
	  if(header[i]!=last && header[i]->value < v)
	    p = header[i];
	  else if(i < no->N)
	    {
	      no->next[i] = header[i];
	      header[i] = no;
	    }
	}
      if(p)
	{
	  while(p->next[i] != last && p->next[i]->value < v)
	    p = p->next[i];
	  if(i < no->N)
	    {
	      no->next[i] = p->next[i];
	      p->next[i] = no; 
	    }
	}
    }
  m_size++;
  return *this;
}


template <class T>
SkipList<T>& SkipList<T>::remove(const T& v)
{
  if(!count(v))
    return *this;
  
  SkipNode<T>* p  = nullptr;
  SkipNode<T>* no = nullptr;
  for(int i=nLevels-1;i>=0;i--)
    {
      if(!p && header[i]!=last)
	{
	  if(header[i]->value < v)
	    p = header[i];
	  else if(header[i]->value == v)
	    {
	      no = header[i];
	      header[i] = no->next[i];
	    }
	}
      if(p)
	{
	  while(p->next[i] != last && p->next[i]->value < v)
	    p = p->next[i];
	  if(p->next[i]->value == v)
	    {
	      if(!no) no = p->next[i];
	      p->next[i] = no->next[i];
	    }
	}
    }
  delete(no);
  while(nLevels && header[nLevels-1] == last)
    {
      header.pop_back();
      nLevels--;
    }
  m_size--;
  return *this;
}


template <class T>
bool SkipList<T>::count(const T& v)
{
  bool found = false;
  SkipNode<T>* p = nullptr;
  for(int i=nLevels-1;!found && i>=0;i--)
    {
      if(!p && header[i]!=last)
	{
	  if(header[i]->value < v)
	    p = header[i];
	  if(header[i]->value == v) found = true;
	}
      if(p)
	{
	  while(p->next[i] != last && p->next[i]->value < v)
	    p = p->next[i];
	  if(p->next[i]->value == v) found = true;
	}
    }
  return found;
}


template <class T>
std::pair<const T&, bool> SkipList<T>::lower_bound(const T& v) // first >=v
{
  if(!count(v))
    return upper_bound(v);
  bool found = false;
  SkipNode<T>* p = nullptr;
  for(int i=nLevels-1;!found && i>=0;i--)
    {
      if(!p && header[i]!=last)
	{
	  if(header[i]->value < v)
	    p = header[i];
	  if(header[i]->value == v)
	    {
	      found = true;
	      p = header[i];
	    }
	  //printf("header %d %d\n", header[i]->value, found);
	}
      if(p)
	{
	  while(p->next[i] != last && p->next[i]->value < v)
	    p = p->next[i];
	  if(p->next[i] != last && p->next[i]->value == v)
	    {
	      found = true;
	      p = p->next[i];
	    }
	}
    }
  return std::make_pair(found? (p->value):v, found);
}


template <class T>
std::pair<const T&, bool> SkipList<T>::upper_bound(const T& v) // first >v
{
  SkipNode<T>* p = nullptr;
  for(int i=nLevels-1;i>=0;i--)
    {
      if(!p && header[i]!=last && header[i]->value <= v)
	p = header[i];
      if(p)
	{
	  while(p->next[i] != last && p->next[i]->value <= v)
	    p = p->next[i];
	}
    }
  if(p)
    p = p->next[0];
  else
    p = header[0];

  if(p!=last)
    return std::make_pair(p->value, true);
  return std::make_pair(v, false);
}


template <class T>
bool SkipList<T>::range_search(const T& l, const T& r)
{
  std::pair<const T&, bool> lb = lower_bound(l);
  return lb.second && lb.first<=r;
}


template <class T>
std::pair<const T&, bool> SkipList<T>::min()
{
  if(!m_size)
    {
      T a;
      return std::make_pair(a,false);
    }
  return std::make_pair(header[0]->value,true);
}


template <class T>
std::pair<const T&, bool> SkipList<T>::max()
{
  if(!m_size)
    {
      T a;
      return std::make_pair(a,false);
    }
  SkipNode<T>* p = nullptr;
  for(int i=nLevels-1;i>=0;i--)
    {
      if(!p && header[i]!=last)
	p = header[i];
      if(p)
	{
	  while(p->next[i] != last)
	    p = p->next[i];
	}
    }
  return std::make_pair(p->value,true);
}


template <class T>
void SkipList<T>::print(int op)
{
  printf("Prob %.3lf  nLevels %u  m_size %u\n", pLevel, nLevels, m_size);
  for(int i=nLevels-1;i>=0;i--)
    {
      printf("Level %d\n", i);
      SkipNode<T>* p = header[i];
      while(p != last)
	{
	  std::cout << " (" << p->value << "," << p->N << ") ->";
	  p = p->next[i];
	}
      printf(" last\n");
    }
  printf("\n");
}
