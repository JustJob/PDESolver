// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file declares the GaussSeidel class.

#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "vector.h"
#include "Matrix.h"
#include "VectorNorm.h"
#include "InvalidMatrix.h"
#include <cmath>

const float EQUAL_THRESHOLD = 0.000001;

template<class T>
class GaussSeidel
{
public:
  //PRE: m should be diagonally dominant and length of sol should be the same 
  // lenth of the columns in m. An exception will be thrown otherwise
  //POST: performs the gauss seidel algorithm that iterates until a solution for 
  // the matrix is found. The solution is said to be found when the distance 
  // from the previous iteration and current iteration is less than the
  // EQUAL_THRESHOLD
  Vector<T> operator()(const BaseMatrix<T>& m, const Vector<T>& sol) const;
};

#include "GaussSeidel.hpp"

#endif