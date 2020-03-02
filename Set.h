#pragma once

template <class T>
class Set
{
public:
  // Capacity
  virtual bool empty()   = 0;
  virtual int  size()    = 0;

  // Modifiers
  virtual void clear()   = 0;
  virtual bool insert()  = 0;
  virtual bool remove()  = 0;
  virtual bool erase()   = 0;

  // Lookup
  virtual int  count()   = 0;
  virtual Set* find()    = 0; // <<<<<<<<<
  virtual T*   lower_b() = 0;
  virtual T*   upper_b() = 0;
  virtual bool range_s() = 0;
}
