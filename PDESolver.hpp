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
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::resize(const ulong size)
{
  m_size = size;
  generateB();
  generateA();
  m_solved = false;
}

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
const SymMatrix<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getA() const
{
  return m_A;
}

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
const Vector<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getB() const
{
  return m_B;
}

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
template<class U>
const Vector<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::solve() const
{
  if(!m_solved)
  {
    U solver;
    m_sol = solver(m_A,m_B);
    m_solved = true;
  }
  return m_sol;
}

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::generateB()
{
  m_B = Vector<T>((m_size - 1) * (m_size - 1));
  ulong index = 0;
  for(ulong i = 1; i < m_size; i++)
  {
    for(ulong j = 1; j < m_size; j++)
    {
      m_B.at(index) = 0;
      if(i - 1 == 0)
        m_B.at(index) += bFunc(((float)j)/m_size);
      if(i + 1 == 0)
        m_B.at(index) += tFunc(((float)j)/m_size);
      if(j - 1 == 0)
        m_B.at(index) += lFunc(((float)i)/m_size);
      if(j - 1 == 0)
        m_B.at(index) += rFunc(((float)i)/m_size);
      index++;
    }
  }
}


template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::generateA()
{
  ulong matSize = (m_size-1)*(m_size-1);
  m_A = SymMatrix<T>(matSize);

  for(ulong i = 0;i<matSize;i++)
  {
    if(i<=matSize-m_size)
    {
      m_A.at(i,i+(m_size-1)) = -.25;
    }
    if((i+1)%(m_size-1)!=0)
    {
      m_A.at(i,i+1) = -.25;
    }
  }
}


