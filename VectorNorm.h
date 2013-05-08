/*
Justin O'Brien
CS328 HW2
02/17/2013

This file defines the VectorNorm class and operators which are friends of it.
*/
#ifndef VECTORNORM_H
#define VECTORNORM_H

#include "vector.h"
#include <math.h>

template<class T>
class VectorNorm
{
public:
  //PRE: None
  //POST: Creates a vector norm with p to signify the pth norm
  // IE: VectorNorm(2) gives the 2nd norm that is called Euclidean 2D Distance
  VectorNorm(unsigned short p) : pNorm(p) {}
  //PRE: None
  //POST: Returns the norm of the Vector. 0 if the vector is empty
  T operator()(const Vector<T>& v) const;
private:
  const unsigned short pNorm;
};

#include "VectorNorm.hpp"
#endif