// Justin O'Brien and Matt Martin
// CS328 Final Project
// 4/2/2013

// This file defines the Cholesky Decomposition class.

template<class T>
Vector<T> CholeskyDecomp<T>::operator()(const SymMatrix<T>& m, 
  const Vector<T>& sol) const
{
  ulong rows = m.numRows();
  Vector<T> retval(rows);
  T ki;
  
  LowerTriangular<T> lower(rows);
  for(unsigned long k = 0; k < rows; k++)
  {
    for(unsigned long i = 0; i <= k; i++)
    {
      ki = m(k,i);
      for(unsigned long j = 0; j < i; j++)
        ki -= lower(i, j) * lower(k, j);
      if(i == k)
        ki = sqrt(ki);
      else
        ki /= lower(i,i);
      lower.at(k,i) = ki;
    }
  }
  Matrix<T> upper(lower);
  Vector<T> temp(rows);
  upper.transpose();

  for(unsigned long i = 0; i < rows; i++)
  {
    ki = sol[i];
    for(unsigned long j = 0; j < i; j++)
    {
      ki -= lower(i,j) * temp[j];
    }
    temp.at(i) = ki/lower(i,i);
  }

  for(unsigned long i = rows; i > 0; i--)
  {
    ki = temp[i-1];
    for(unsigned long j = rows; j > i; j--)
    {
      ki -= upper(i-1, j-1) * retval[j-1];
    }
    retval.at(i-1) = ki/upper(i-1, i-1);
  }

  return retval;
}