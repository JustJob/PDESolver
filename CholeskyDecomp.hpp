// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file defines the Choleski Decomposition class.

template<class T>
Vector<T> CholeskyDecomp<T>::operator()(const SymMatrix<T>& m, 
  const Vector<T>& sol) const
{
  Vector<T> retval(m.numRows());
  
  LowerTriangular<T> lower(m.numRows());
  for(unsigned long k = 0; k < m.numRows(); k++)
  {
    for(unsigned long i = 0; i <= k; i++)
    {
      lower.at(k, i) = m(k, i);
      for(unsigned long j = 0; j < i; j++)
        lower.at(k, i) -= lower(i, j) * lower(k, j);
      if(i == k)
        lower.at(k,i) = sqrt(lower(k,i));
      else
        lower.at(k,i) /= lower(i,i);
    }
  }
  Matrix<T> upper(lower);
  Vector<T> temp(m.numRows());
  upper.transpose();

  for(unsigned long i = 0; i < sol.size(); i++)
  {
    temp.at(i) = sol[i];
    for(unsigned long j = 0; j < i; j++)
    {
      temp.at(i) -= lower(i,j) * temp[j];
    }
    temp.at(i) /= lower(i,i);
  }

  for(unsigned long i = sol.size(); i > 0; i--)
  {
    retval.at(i-1) = temp[i-1];
    for(unsigned long j = sol.size(); j > i; j--)
    {
      retval.at(i-1) -= upper(i-1, j-1) * retval[j-1];
    }
    retval.at(i-1) /= upper(i-1, i-1);
  }

  return retval;
}