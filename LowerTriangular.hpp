// Justin O'Brien
// cs328 hw5
// 4/2/2013

template<class T>
LowerTriangular<T>::LowerTriangular(unsigned long rows) : 
  Matrix<T>()
{
  if(!rows)
    throw InvalidMatrix("Matrix with 0 rows and 0 columns");
  Matrix<T>::m_rows = Matrix<T>::m_cols = rows;
  Matrix<T>::data = new Vector<T>[rows];
  for(unsigned long i = 0; i < rows; i++)
  {
    Matrix<T>::data[i] = Vector<T>(rows, 0, rows - i - 1);
    for(unsigned long j = 0; j <= i; j++)
      Matrix<T>::data[i].at(j) = 0;
  }
}

template<class T>
Matrix<T>& LowerTriangular<T>::operator=(const LowerTriangular<T>& rhs)
{
  return Matrix<T>::operator=((Matrix<T>&)rhs);
}

template<class T>
Vector<T> LowerTriangular<T>::getCol(unsigned long i) const
{
  if(i >= Matrix<T>::m_cols)
    throw InvalidIndex(i);

  Vector<T> retval(Matrix<T>::m_cols, i, 0);
  for(unsigned long j = i; j < Matrix<T>::m_cols; j++)
    retval.at(j) = Matrix<T>::operator()(j, i);
  return retval;
}


template<class T>
Matrix<T> LowerTriangular<T>::operator*(const BaseMatrix<T>& rhs) const
{
  return Matrix<T>::operator*(rhs);
}

template<class T>
LowerTriangular<T> LowerTriangular<T>::operator*(const LowerTriangular<T>& rhs)
{
  if(Matrix<T>::numCols() != rhs.numRows())
    throw InvalidVectorMath("Trying to multiply two incompatable matrices");

  LowerTriangular<T> retval(rhs.numRows());
  for(unsigned long i = 0; i < rhs.numRows(); i++)
    for(unsigned long j = 0; j <= i; j++)
      retval.at(i,j) = Matrix<T>::getRow(i) * rhs.getCol(j);
  return retval;
}