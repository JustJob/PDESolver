// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file defined the PDESolver class.

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
PDESolver<T,lFunc,rFunc,bFunc,tFunc>::PDESolver(const ulong size, 
            const T lBound, const T rBound, const T bBound, const T tBound)
{
  m_size = size;
  if(lBound >= rBound)
    throw InvalidBound("Left bound needs to be less than right bound");
  if(bBound >= tBound)
    throw InvalidBound("Lower bound needs to be less than upper bound");
  m_leftBound = lBound;
  m_rightBound = rBound;
  m_upperBound = tBound;
  m_lowerBound = bBound;
  generateB();
  generateA();
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc>::resize(const ulong size)
{
  if(size != m_size)
  {
    m_size = size;
    generateB();
    generateA();
  }
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
const SymMatrix<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getA() const
{
  return m_A;
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
const Vector<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc>::getB() const
{
  return m_B;
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
template<class U>
const Vector<T> PDESolver<T,lFunc,rFunc,bFunc,tFunc>::solve() const
{
  U solver;
  return solver(m_A,m_B);
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
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
        m_B.at(index) += bFunc(((T)j * (m_rightBound - m_leftBound))/m_size + m_leftBound);
      if(i + 1 == m_size)
        m_B.at(index) += tFunc(((T)j * (m_rightBound - m_leftBound))/m_size + m_leftBound);
      if(j - 1 == 0)
        m_B.at(index) += lFunc(((T)i * (m_upperBound - m_lowerBound))/m_size + m_lowerBound);
      if(j + 1 == m_size)
        m_B.at(index) += rFunc(((T)i * (m_upperBound - m_lowerBound))/m_size + m_lowerBound);
      m_B.at(index) /= 4;
      index++;
    }
  }
}


template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T)>
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
    m_A.at(i,i) = 1;
  }
}


