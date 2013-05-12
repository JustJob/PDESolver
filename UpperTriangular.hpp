// Justin O'Brien and Matt Martin
// CS328 Final Project
// 4/2/2013

// This file defines the upper triangular matrix class.

template<class T>
UpperTriangular<T>::UpperTriangular(unsigned long rows) : 
  Matrix<T>()
{
  if(!rows)
    throw InvalidMatrix("Matrix with 0 rows and 0 columns");
  Matrix<T>::m_rows = Matrix<T>::m_cols = rows;
  Matrix<T>::data = new Vector<T>[rows];
  for(unsigned long i = 0; i < rows; i++)
  {
    Matrix<T>::data[i] = Vector<T>(rows, i, 0);
    for(unsigned long j = i; j < rows; j++)
      Matrix<T>::data[i].at(j) = 0;
  }
}

template<class T>
Matrix<T>& UpperTriangular<T>::operator=(const UpperTriangular<T>& rhs)
{
  return Matrix<T>::operator=((Matrix<T>&)rhs);
}

template<class T>
Vector<T> UpperTriangular<T>::getCol(unsigned long i) const
{
  if(i >= Matrix<T>::m_cols)
    throw InvalidIndex(i);

  Vector<T> retval(Matrix<T>::m_cols, 0, Matrix<T>::m_cols - i - 1);
  for(unsigned long j = 0; j <= i; j++)
    retval.at(j) = Matrix<T>::operator()(j, i);
  return retval;
}

template<class T>
Matrix<T> UpperTriangular<T>::operator*(const BaseMatrix<T>& rhs) const
{
  return Matrix<T>::operator*(rhs);
}

template<class T>
UpperTriangular<T> UpperTriangular<T>::operator*(const UpperTriangular<T>& rhs)
{
  if(Matrix<T>::numCols() != rhs.numRows())
    throw InvalidVectorMath("Trying to multiply two incompatable matrices");

  UpperTriangular<T> retval(rhs.numRows());
  for(unsigned long i = 0; i < rhs.numRows(); i++)
    for(unsigned long j = i; j < rhs.numRows(); j++)
      retval.at(i,j) = Matrix<T>::getRow(i) * rhs.getCol(j);
  return retval;
}