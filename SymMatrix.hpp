// Justin O'Brien and Matt Martin
// CS328 Final Project
// 4/2/2013

// This file defines the symetric matrix class.

template<class T>
T& SymMatrix<T>::at(unsigned long row, unsigned long col)
{
  if(row >= Matrix<T>::numRows())
    throw InvalidIndex(row);
  if(col < row)
    return Matrix<T>::data[col].at(row);
  else
    return Matrix<T>::data[row].at(col);
}

template<class T>
const T& SymMatrix<T>::operator()(unsigned long row, unsigned long col) const
{
  if(row >= Matrix<T>::numRows())
    throw InvalidIndex(row);
  if(col < row)
    return Matrix<T>::data[col][row];
  else
    return Matrix<T>::data[row][col];
}

template<class T>
Matrix<T>& SymMatrix<T>::operator=(const SymMatrix<T>& rhs)
{
  return Matrix<T>::operator=((Matrix<T>&)rhs);
}

template<class T>
Matrix<T> SymMatrix<T>::operator*(const BaseMatrix<T>& rhs) const
{
  if(Matrix<T>::numCols() != rhs.numRows())
    throw InvalidVectorMath("Trying to multiply two incompatable matrices");

  Matrix<T> retval(Matrix<T>::numRows(), rhs.numCols());
  for(unsigned long i = 0; i < Matrix<T>::numRows(); i++)
    for(unsigned long j = 0; j < rhs.numCols(); j++)
      for(unsigned long k = 0; k < rhs.numCols(); k++)
        retval.at(i,j) += (*this)(i,k) * rhs(k, j);
  return retval;
}