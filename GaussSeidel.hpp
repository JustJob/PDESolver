// Justin O'Brien and Matt Martin
// CS328 Final Project
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
  int i = 0;

  for(ulong i = 0; i < retval.size(); i++)
  {
    retval.at(i) = 0.5; //initial guess
  }

  do
  {
    i++;
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

  cout << "iterations was " << i << endl;

  return retval;
}