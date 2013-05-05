// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file declares the symetric matrix class.

#ifndef SYM_MATRIX_H
#define SYM_MATRIX_H

#include "Matrix.h"
#include "BaseMatrix.h"
#include "Vector.h"
#include "InvalidVectorMath.h"
#include "invalidIndex.h"
#include "InvalidMatrix.h"

template<class T>
class SymMatrix : public virtual Matrix<T>, public virtual BaseMatrix<T>,
  private virtual UpperTriangular<T>
{
public:
  //PRE: None
  //POST: creates a symmetric matrix with no members set
  SymMatrix() {}
  //PRE: None
  //POST: creates a symmetric matrix by calling the uppertriagular constructor
  // only stores the upper half of values and uses indexing switches to control
  // access
  SymMatrix(unsigned long rows) : UpperTriangular<T>(rows) {}
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  // if row > col then the indexes will be switched so it will appear to have
  // data in all spaces and not just half
  virtual T& at(unsigned long row, unsigned long col);
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  // if row > col then the indexes will be switched so it will appear to have
  // data in all spaces and not just half
  virtual const T& operator()(unsigned long row, unsigned long col) const;
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const SymMatrix<T>& rhs);
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result.
  virtual Matrix<T> operator*(const BaseMatrix<T>& rhs) const;
};

#include "SymMatrix.hpp"

#endif