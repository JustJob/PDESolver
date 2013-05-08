// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file defines the GaussSeidel class.

template<class T>
Vector<T> GaussSeidel<T>::operator()(const BaseMatrix<T>& m, 
                                    const Vector<T>& sol) const
{
  T prev;
  for(unsigned long i = 0; i < m.numRows(); i++)
  {
    prev = m(i,i);
    for(unsigned long j = 0; j < m.numCols(); j++)
    {
      if(i != j && abs(prev) < abs(m(i,j)))
        throw InvalidMatrix("Matrix is non-diagonally dominant");
    }
  }
  VectorNorm<T> norm(2);
  Vector<T> retval(m.numCols());

  do
  {
    prev = norm(retval);
    for(unsigned long i = 0; i < sol.size(); i++)
    {
      retval.at(i) = sol[i];
      for(unsigned long j = 0; j < sol.size(); j++)
        if(j != i)
          retval.at(i) -= retval[j] * m(i,j);
      retval.at(i) /= m(i,i);
    }
  } while(abs(prev - norm(retval)) > EQUAL_THRESHOLD);

  return retval;
}