// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file declares the Base Matrix abstract class.

#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H

#include "vector.h"

template<class T>
class BaseMatrix
{
public:
  //PRE: rows must be equal to null or existing data
  //POST: destructs the matrix
  virtual ~BaseMatrix() {}
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  virtual T& at(unsigned long row, unsigned long col) = 0;
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  virtual const T& operator()(unsigned long row, unsigned long col) const = 0;
  //PRE: operator= must be defined on T objects
  //POST: sets this matrix equal to it's transpose and returns the transpose
  virtual BaseMatrix<T>& transpose() = 0;
  //PRE: T objects must have operator* defined
  //POST: multiplies the two matrices and stores result in current matrix
  virtual BaseMatrix<T>& operator*=(const BaseMatrix<T>& rhs) = 0;
  //PRE: T objects must have operator* defined
  //POST: Sets each value in the matrix to c mutliplied by the term
  virtual BaseMatrix<T>& operator*=(const T& c) = 0;
  //PRE: T objects must have operator+ defined
  //POST: Adds the current matrix and rhs and stores result in current matrix
  virtual BaseMatrix<T>& operator+=(const BaseMatrix<T>& rhs) = 0;
  //PRE: T objects must have operator- defined
  //POST: Subtracts rhs from the matrix and stores the result in current matrix
  virtual BaseMatrix<T>& operator-=(const BaseMatrix<T>& rhs) = 0;
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual BaseMatrix<T>& operator=(const BaseMatrix<T>& rhs) = 0;
  //PRE: None
  //POST: returns the number of rows
  virtual unsigned long numRows() const = 0;
  //PRE: None
  //POST: returns the number of columns
  virtual unsigned long numCols() const = 0;
  //PRE: i should be less than number of rows
  //POST: returns the reference to the row at index i
  virtual Vector<T>& getRow(unsigned long i) const = 0;
  //PRE: i should be less than number of cols
  //POST: returns a copy of the column at index i
  virtual Vector<T> getCol(unsigned long i) const = 0;
};

#endif