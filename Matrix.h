// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file declares the matrix class.

#ifndef MATRIX_H
#define MATRIX_H

#include "BaseMatrix.h"
#include "vector.h"
#include "InvalidMatrix.h"
#include <iostream>

template<class T>
class Matrix : public virtual BaseMatrix<T>
{
public:
  //PRE: None
  //POST: creates a dense matrix with all positions set to 0
  Matrix(unsigned long rows, unsigned long cols);
  //PRE: None
  //POST: copies the rows of rhs into this matrix
  Matrix(const Matrix<T>& rhs);
  //PRE: None
  //POST: copies the rows of rhs into this matrix
  Matrix(const BaseMatrix<T>& rhs);
  //PRE: rows must be equal to null or existing data
  //POST: destructs the matrix
  virtual ~Matrix();
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  // an invalid index will also be thrown if this function is called on a place
  // that cannot be modified. Ex: at(1,2) on a diagonal matrix will error out
  virtual T& at(unsigned long row, unsigned long col);
  //PRE: None
  //POST: returns the element at row and col and if is out of range an 
  // InvalidIndex exception will be thrown
  virtual const T& operator()(unsigned long row, unsigned long col) const;
  //PRE: T objects must have operator* defined
  //POST: multiplies the two matrices and stores result in current matrix
  virtual Matrix<T>& operator*=(const BaseMatrix<T>& rhs);
  //PRE: T objects must have operator* defined
  //POST: Sets each value in the matrix to c mutliplied by the term
  virtual Matrix<T>& operator*=(const T& c);
  //PRE: T objects must have operator+ defined
  //POST: Adds the current matrix and rhs and stores result in current matrix
  virtual Matrix<T>& operator+=(const BaseMatrix<T>& rhs);
  //PRE: T objects must have operator- defined
  //POST: Subtracts rhs from the matrix and stores the result in current matrix
  virtual Matrix<T>& operator-=(const BaseMatrix<T>& rhs);
  //PRE: operator= must be defined on T objects
  //POST: returns a new matrix that is the transpose of the current matrix
  virtual Matrix<T>& transpose();
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const BaseMatrix<T>& rhs);
  //PRE: operator= must be defined on T objects
  //POST: creates a deep copy of the current matrix
  virtual Matrix<T>& operator=(const Matrix<T>& rhs);
  //PRE: operator=, operator+, and operator* must be defined on T objects
  //POST: multiples this matrix by rhs and creates a new matrix that is set
  // to the result.
  virtual Matrix<T> operator*(const BaseMatrix<T>& rhs) const;
  //PRE: None
  //POST: returns the number of rows
  virtual unsigned long numRows() const;
  //PRE: None
  //POST: returns the number of columns
  virtual unsigned long numCols() const;

protected:
  //PRE: i should be less than number of rows
  //POST: returns the reference to the row at index i
  virtual Vector<T>& getRow(unsigned long i) const;
  //PRE: i should be less than number of cols
  //POST: returns a copy of the column at index i
  virtual Vector<T> getCol(unsigned long i) const;
  //PRE: None
  //POST: creates a lower triagular matrix with no members set
  Matrix() : data(NULL) {}

  unsigned long m_rows; //stores the number of rows in matrix
  unsigned long m_cols; //stores the number of columns in the matrix
  Vector<T>* data; //data contains vectors and data in the matrix

  template<class U>
  friend Vector<U> operator*(const BaseMatrix<U>& lhs, const Vector<U>& rhs);
  template<class U>
  friend Matrix<U> operator*(const BaseMatrix<U>& lhs, const U& c);
};

//PRE: T objects must have operator* and operator+ defined
//POST: multiplies this matrix by the Vector rhs and returns the resultant
// vector
template<class T>
Vector<T> operator*(const BaseMatrix<T>& lhs, const Vector<T>& rhs);
//PRE: T objects must have operator* and operator+ defined
//POST: multiplies this matrix by the constant c and returns the result
template<class T>
Matrix<T> operator*(const BaseMatrix<T>& lhs, const T& c);
template<class T>
//PRE: T objects must have operator+ defined
//POST: adds this matrix by the Vector rhs and returns the resultant
// vector
Matrix<T> operator+(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs);
//PRE: T objects must have operator- defined
//POST: subtracts rhs from this matrix returns the resultant vector
template<class T>
Matrix<T> operator-(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs);
//PRE: operator== must be defined on T
//POST: returns whether the this matrix is equal to rhs. True is yes.
template<class T>
bool operator==(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs);
//PRE: operator!= must be defined on T
//POST: returns whether the this matrix is equal to rhs. False is yes.  
template<class T>
bool operator!=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs);
//PRE: none
//POST: outputs the matrix with each row on a single line with data seperated
// by tabs
template<class T>
ostream& operator<<(ostream& out, const BaseMatrix<T>& rhs);
//PRE: rhs should be the zero matrix
//POST: inputs the matrix and attempts to fill the matrix completely with data
// this will overwrite any current data. This function will skip zero valued 
// inputs so if data exists in rhs that is non-zero and the input at that 
// position is zero it will be skipped and the non-zero value will remain
template<class T>
istream& operator>>(istream& in, BaseMatrix<T>& rhs);

#include "Matrix.hpp"

#endif