// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file declares the upper triangular matrix class.

#ifndef UPPER_TRI_H
#define UPPER_TRI_H

#include "Matrix.h"
#include "BaseMatrix.h"
#include "vector.h"
#include "InvalidVectorMath.h"
#include "invalidIndex.h"
#include "InvalidMatrix.h"

template<class T>
class UpperTriangular : public virtual Matrix<T>, public virtual BaseMatrix<T>
{
public:
  //PRE: None
  //POST: creates a upper triagular matrix with no members set
  UpperTriangular() {}
  //PRE: None
  //POST: creates a upper triangular matrix with everything set to zero
  // it also only allows the upper half of the matrix to be modified
  UpperTriangular(unsigned long rows);
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const UpperTriangular<T>& rhs);
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result.
  virtual Matrix<T> operator*(const BaseMatrix<T>& rhs) const;
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result. The resultant is a upper triangular matrix.
  virtual UpperTriangular<T> operator*(const UpperTriangular<T>& rhs);
protected:
  //PRE: i must be less than the number of columsn
  //POST: returns an optimized column vector that only has the approriate data
  // values and doesn't store the zeros
  virtual Vector<T> getCol(unsigned long i) const;
};

#include "UpperTriangular.hpp"

#endif