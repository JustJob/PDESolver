// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file defined the PDESolver class.


template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
PDESolver<T,lFunc,rFunc,bFunc,tFunc>::PDESolver(const ulong size, 
            const T lBound, const T rBound, const T tBound, const T bBound)
{
  m_size = size;
  m_leftBound = lBound;
  m_rightBound = rBound;
  m_upperBound = tBound;
  m_lowerBound = bBound;
  m_solved = false;
  generateB();
  generateA();
}

template<class T, double lFunc(double), double rFunc(double),
         double bFunc(double), double tFunc(double)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::resize(const ulong size);

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
const SymMatrix<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getA() const;

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
const Vector<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getB() const;

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
template<class U>
Vector<T> PDESolver<T,lFunc,rFunc,bFunc,tFunc>::solve<U>() const;

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::generateB()
{
  m_sol = Vector<T>((m_size - 1) * (m_size - 1));
  ulong index = 0;
  for(ulong i = 1; i < m_size; i++)
  {
    for(ulong j = 1; j < m_size; j++)
    {
      m_sol[index] = 0;
      if(i - 1 == 0)
        m_sol[index] += bFunc(((float)j)/m_size);
      if(i + 1 == 0)
        m_sol[index] += tFunc(((float)j)/m_size);
      if(j - 1 == 0)
        m_sol[index] += lFunc(((float)i)/m_size);
      if(j - 1 == 0)
        m_sol[index] += rFunc(((float)i)/m_size);
      index++;
    }
  }
}