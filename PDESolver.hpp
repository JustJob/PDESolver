// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file defined the PDESolver class.

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::PDESolver(const ulong size, 
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

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::resize(const ulong size)
{
  if(size != m_size)
  {
    m_size = size;
    generateB();
    generateA();
  }
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
const SymMatrix<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::getA() const
{
  return m_A;
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
const Vector<T>& PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::getB() const
{
  return m_B;
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
template<class U>
const Vector<T> PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::solve() const
{
  U solver;
  return solver(m_A,m_B);
}

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::generateB()
{
  m_B = Vector<T>((m_size - 1) * (m_size - 1));
  ulong index = 0;
  T hVal = (m_rightBound - m_leftBound) / ((T)m_size);
  T x,y;
  for(ulong i = 1; i < m_size; i++)
  {
    for(ulong j = 1; j < m_size; j++)
    {
      m_B.at(index) = 0;
      x = ((T)j * (m_rightBound - m_leftBound))/m_size + m_leftBound;
      y = ((T)i * (m_upperBound - m_lowerBound))/m_size + m_lowerBound;
      if(i - 1 == 0)
        m_B.at(index) += bFunc(x);
      if(i + 1 == m_size)
        m_B.at(index) += tFunc(x);
      if(j - 1 == 0)
        m_B.at(index) += lFunc(y);
      if(j + 1 == m_size)
        m_B.at(index) += rFunc(y);
      m_B.at(index) -= hVal*hVal*force(x,y);
      m_B.at(index) /= 4;
      index++;
    }
  }
}


template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::generateA()
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


template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
void PDESolver<T,lFunc,rFunc,bFunc,tFunc,force>::gnuPlotify(Vector<T>& sol,const string &method)
{
  string size;
  stringstream strStream;
  strStream<<m_size;
  strStream>>size;
  
  
  ofstream pnts,up,down,left,right;
  pnts.open(("points"+method+size+".dat").c_str());

  up.open(("up"+method+size+".dat").c_str());
  down.open(("down"+method+size+".dat").c_str());
  left.open(("left"+method+size+".dat").c_str());
  right.open(("right"+method+size+".dat").c_str());
  
  T val = (m_upperBound-m_lowerBound)/m_size;

  for(unsigned long i = 0;i<m_size;i++)
  {
    up<<m_upperBound<<","<<val<<","<<tFunc(val)<<endl;
    down<<m_lowerBound<<","<<val<<","<<bFunc(val)<<endl;
    left<<val<<","<<m_leftBound<<","<<lFunc(val)<<endl;
    right<<val<<","<<m_rightBound<<","<<rFunc(val)<<endl;
  }

  for(unsigned long i = 0;i<(m_size-1)*(m_size-1);i++)
  {
    T y = i/(m_size-1);
    T x = i%(m_size-1);

    pnts<<x*val<<", "<<y*val<<", "<<sol[i]<<endl;
  }
  pnts.close();
  up.close();
  down.close();
  left.close();
  right.close();
}
