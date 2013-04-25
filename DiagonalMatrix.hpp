// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file defines the diagonal matrix class.

template<class T>
DiagonalMatrix<T>::DiagonalMatrix(unsigned long rows) : 
  Matrix<T>()
{
  if(!rows)
    throw InvalidMatrix("Matrix with 0 rows and 0 columns");
  Matrix<T>::m_rows = Matrix<T>::m_cols = rows;
  Matrix<T>::data = new Vector<T>[rows];
  for(unsigned long i = 0; i < rows; i++)
  {
    Matrix<T>::data[i] = Vector<T>(rows, i, rows - i - 1);
    Matrix<T>::data[i].at(i) = 0;
  }
}

template<class T>
Matrix<T>& DiagonalMatrix<T>::operator=(const DiagonalMatrix<T>& rhs)
{
  return Matrix<T>::operator=((Matrix<T>&)rhs);
}

template<class T>
Vector<T> DiagonalMatrix<T>::getCol(unsigned long i) const
{
  if(i >= Matrix<T>::m_cols)
    throw InvalidIndex(i);

  Vector<T> retval(Matrix<T>::m_cols, i, Matrix<T>::m_cols - i - 1);
  retval.at(i) = Matrix<T>::operator()(i,i);
  return retval;
}

template<class T>
Matrix<T> DiagonalMatrix<T>::operator*(const BaseMatrix<T>& rhs) const
{
  return Matrix<T>::operator*(rhs);
}

template<class T>
DiagonalMatrix<T> DiagonalMatrix<T>::operator*(const DiagonalMatrix<T>& rhs)
{
  if(Matrix<T>::numCols() != rhs.numRows())
    throw InvalidVectorMath("Trying to multiply two incompatable matrices");

  DiagonalMatrix<T> retval(rhs.numRows());
  for(unsigned long i = 0; i < rhs.numRows(); i++)
  {
    retval.at(i,i) = Matrix<T>::getRow(i) * rhs.getCol(i);
  }

  return retval;
}