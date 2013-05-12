//Justin O'Brien and Matt Martin
//CS328 Final Project
//Instructor: Clayton Price
//Date: 02/25/2013
//This file defines the vector class and operators which are friends of it.

#ifndef VECTOR_H
#define VECTOR_H

#include "invalidIndex.h"
#include "InvalidVectorMath.h"
#include <math.h>

typedef unsigned long ulong;

template<class T>
class Vector
{
 public:
  Vector() : m_data(NULL), m_zero(0) {}
  //PRE: None
  //POST: Initializes the size to the m_size param and sets
  // the left and right offsets to the passed in values
  Vector(const ulong p_size, ulong p_loffset = 0, ulong p_roffset = 0);

  //PRE: None
  //POST: Clears the current contents of the array and then creates a duplicate 
  // of v.
  Vector(const Vector& v);

  //PRE: None
  //POST: Destructs the vector and releases the memory
  ~Vector();

  //PRE: None
  //POST: Returns the size
  ulong size() const;

  //PRE: T must be a type that has the operator* and operator+ defined and 
  // should add and multiply the two T objects, the T object should also be
  // accepted by the sqrt function from math.h
  //POST: returns the magnitude of the vector which is the sum of its sqared 
  // parts
  T mag() const;

  //PRE: T must have the operator* defined and operator/
  //POST: returns the normalized version of the current vector. That is the 
  // vector that has a magnitude of 1 and points in the same direction
  Vector normalize() const;

  //PRE: T objects must have operator= defined
  //POST: Clears the current contents of the array and then creates a duplicate 
  // of v and returns the new vector
  Vector& operator=(const Vector& v);

  //PRE: None
  //POST: Retreives a writeable reference to the data item at p within the 
  // container. If no data item exists at p then an InvalidIndex is thrown.
  // an invalidindex is also thrown if p < m_loff or p >= m_size-m_roff
  T& at(const ulong p);

  //PRE: None
  //POST: Retreives a writeable reference to the data item at p within the 
  // container. If no data item exists at p then an InvalidIndex is thrown.
  // if p falls in the offset then a zero is returned
  const T& operator[](const ulong p) const;

  //PRE: T objects must have the operator* defined
  //POST: takes the inner product of the current vector and vector v and returns
  // the result. Only multiplies the positions it needs to by checking offsets
  // of bost vectors
  T operator*(const Vector& v) const;

  //PRE: T objects must have the operator+ defined
  //POST: takes the sum of the current vector and vector v and returns
  // the result. Only adds the positions it needs to by checking offsets
  // of bost vectors
  Vector operator+(const Vector& v) const;

  //PRE: T objects must have the operator+ defined
  //POST: takes the sum of the current vector and vector v and returns
  // the result, this changes the calling object to the returned value
  Vector& operator+=(const Vector& v);

  //PRE: T objects must have the operator- defined
  //POST: takes the sum of the current vector and vector v and returns
  // the result. Only subtracts the positions it needs to by checking offsets
  // of bost vectors
  Vector operator-(const Vector& v) const;

  //PRE: T objects must have the operator- defined
  //POST: takes the sum of the current vector and vector v and returns
  // the result, this changes the calling object to the returned value
  Vector& operator-=(const Vector& v);

  //PRE: T objects must have the operator* defined
  //POST: takes the scalar product of the value c with the current vector and
  // returns the result. Only multiplies the positions it needs to by checking 
  // offsets of bost vectors
  Vector operator*(const T& c) const;

  //PRE: T objects must have the operator* defined
  //POST: takes the scalar product of the value c with the current vector and
  // returns the result, this changes the value of the calling object to the 
  //returned value
  Vector& operator*=(const T& c);

  //PRE: T objects must have the operator== defined
  //POST: checks whether all the values in the vector are equivalent and returns
  // true if they are
  bool operator==(const Vector& v) const;

  //PRE: T objects must have the operator== defined
  //POST: checks whether all the values in the vector are equivalent and returns
  // false if they are
  bool operator!=(const Vector& v) const;
  
 private:
  ulong m_size; //size of vector
  ulong m_loffset; //amount of zeros on the left side of the vector
  ulong m_roffset; //amount of zeros on the right side of the vector
  T* m_data; //data that isn't the outer zeros
  const T m_zero; //a zero value to return when in the offset
};

//PRE: None
//POST: outputs the vector on to out in the order. Uses one line
template<class T>
ostream& operator<<(ostream& out, const Vector<T>& rhs);
//PRE: in has enough data to fill up rhs until max_size
//POST: fills the Vector from the beginning until its max_size is reached
template<class T>
istream& operator>>(istream& in, Vector<T>& rhs);

#include"vector.hpp"
#endif
