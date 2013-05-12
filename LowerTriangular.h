// Justin O'Brien and Matt Martin
// CS328 Final Project
// 4/2/2013

// This file declares the lower triangular matrix class.

#ifndef LOWER_TRI_H
#define LOWER_TRI_H

#include "Matrix.h"
#include "BaseMatrix.h"
#include "vector.h"
#include "InvalidVectorMath.h"
#include "invalidIndex.h"
#include "InvalidMatrix.h"

template<class T>
class LowerTriangular : public virtual Matrix<T>, public virtual BaseMatrix<T>
{
public:
  //PRE: None
  //POST: creates a lower triagular matrix with no members set
  LowerTriangular() {}
  //PRE: None
  //POST: creates a lower triangular matrix with everything set to zero
  // it also only allows the lower half of the matrix to be modified
  LowerTriangular(unsigned long rows);
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const LowerTriangular<T>& rhs);
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result.
  virtual Matrix<T> operator*(const BaseMatrix<T>& rhs) const;
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result. The resultant is a lower triangular matrix.
  virtual LowerTriangular<T> operator*(const LowerTriangular<T>& rhs);
protected:
  //PRE: i must be less than the number of columsn
  //POST: returns an optimized column vector that only has the approriate data
  // values and doesn't store the zeros
  virtual Vector<T> getCol(unsigned long i) const;
};

#include "LowerTriangular.hpp"

#endif