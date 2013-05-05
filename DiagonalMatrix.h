// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file declares the diagonal matrix class.

#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

#include "Matrix.h"
#include "BaseMatrix.h"
#include "Vector.h"
#include "InvalidVectorMath.h"
#include "invalidIndex.h"
#include "InvalidMatrix.h"

template<class T>
class DiagonalMatrix : public virtual Matrix<T>, public virtual BaseMatrix<T>
{
public:
  //PRE: None
  //POST: creates a diagonal matrix with no members set
  DiagonalMatrix() {}
  //PRE: None
  //POST: creates a diagonal matrix with everything set to zero
  // it also only allows the diagonal of the matrix to be modified
  DiagonalMatrix(unsigned long rows);
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const DiagonalMatrix<T>& rhs);
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result.
  virtual Matrix<T> operator*(const BaseMatrix<T>& rhs) const;
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result. The resultant is a diagonal matrix.
  virtual DiagonalMatrix<T> operator*(const DiagonalMatrix<T>& rhs);
protected:
  //PRE: i must be less than the number of columsn
  //POST: returns an optimized column vector that only has one data value
  // and doesn't store the zeros
  virtual Vector<T> getCol(unsigned long i) const;
};

#include "DiagonalMatrix.hpp"

#endif