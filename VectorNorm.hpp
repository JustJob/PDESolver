/*
Justin O'Brien and Matt Martin
CS328 Final Project
02/17/2013

This file declares the VectorNorm class and operators which are friends of it.
*/

#include "VectorNorm.h"

template<class T>
T VectorNorm<T>::operator()(const Vector<T> & v) const
{
  T retval = 0;
  for(unsigned long i = 0; i < v.size(); i++)
    retval += pow(v[i], pNorm);

  retval = pow(retval, 1.0/pNorm);
  return retval;
}