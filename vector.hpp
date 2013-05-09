//Justin O'Brien
//CS328 Assignment 6
//Instructor: Clayton Price
//Date: 02/25/2013
//This file declares the quaternion class and operators which are friends of it.

//construtor for vector which initiallizes size to 0, max size to 1, and the 
//underlying array to a new array of max size
template<class T>
Vector<T>::Vector(const ulong p_size, ulong p_loffset, ulong p_roffset)\
  : m_size(p_size), m_loffset(p_loffset), m_roffset(p_roffset), m_zero(0)
{
  if(m_loffset + m_roffset == m_size)
    throw InvalidVectorMath("Can't have offsets overlap");
  m_data = new T[m_size - m_loffset - m_roffset];

  for(ulong i = 0; i < m_size - m_loffset - m_roffset; i++)
    m_data[i] = 0;
}

//this construtor makes a new copy of vector v
template<class T>
Vector<T>::Vector(const Vector& v) : m_zero(0)
{
  m_data = NULL;
  *this = v;
}

//this deletes the memory stored in m_data so no memory is leaked
template<class T>
Vector<T>::~Vector()
{
  if(m_data) delete [] m_data;
}

template<class T>
ulong Vector<T>::size() const
{
  return m_size;
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
  if(m_data) delete [] m_data;
  
  m_size = v.m_size;
  m_roffset = v.m_roffset;
  m_loffset = v.m_loffset;
  
  m_data = new T[m_size - m_loffset - m_roffset];
  
  for(ulong i = 0; i < m_size - m_loffset - m_roffset; i++)
    m_data[i] = v.m_data[i];
  
  return *this;
}

template<class T>
T& Vector<T>::at(const ulong p)
{
  if(p >= m_size - m_roffset || p < m_loffset)
    throw InvalidIndex(p);
  return m_data[p - m_loffset];
}

template<class T>
const T& Vector<T>::operator[](const ulong p) const
{
  if(p >= m_size)
    throw InvalidIndex(p);
  if(p < m_loffset || p >= m_size - m_roffset)
    return m_zero;
  return m_data[p - m_loffset];
}

template<class T>
T Vector<T>::operator*(const Vector& v) const
{
  if(size() != v.size()) 
  {
    throw InvalidVectorMath("The sizes of the vectors do not match when \
                             taking the inner product");
  }

  T retval = 0;
  ulong firstNonZero = m_loffset > v.m_loffset ? m_loffset : v.m_loffset;
  ulong lastNonZero = m_size- (m_roffset>v.m_roffset ? m_roffset : v.m_roffset);
  for(ulong i = firstNonZero; i < lastNonZero; i++)
  {
    retval += (*this)[i] * v[i];
  }

  return retval;
}

template<class T>
T Vector<T>::mag() const
{
  T retval = 0;
  for(ulong i = 0; i < m_size - m_loffset - m_roffset; i++)
  {
    retval += m_data[i] * m_data[i];
  }
  return T(sqrt(retval));
}

template<class T>
Vector<T> Vector<T>::normalize() const
{
  T thisMag = mag();
  Vector<T> retval = Vector<T>(m_size, m_loffset, m_roffset);
  for(ulong i = 0; i < m_size - m_loffset - m_roffset; i++)
  {
    retval[i] = m_data[i] * (1/thisMag);
  }
  return retval;
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector& v) const
{
  if(size() != v.size()) 
  {
    throw InvalidVectorMath("The sizes of the vectors do not match when \
                             taking the sum of two vectors");
  }

  ulong firstNonZero = m_loffset < v.m_loffset ? m_loffset : v.m_loffset;
  ulong lastNonZero = m_roffset < v.m_roffset ? m_roffset : v.m_roffset;
  Vector<T> retval = Vector<T>(m_size, firstNonZero, lastNonZero);
  for(ulong i = firstNonZero; i < m_size - lastNonZero; i++)
    retval.at(i) = ((*this)[i] + v[i]);
  return retval;
}

template<class T>
Vector<T>& Vector<T>::operator+=(const Vector& v)
{
  return (*this = *this + v);
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector& v) const
{
  if(size() != v.size()) 
  {
    throw InvalidVectorMath("The sizes of the vectors do not match when \
                             taking the sum of two vectors");
  }

  ulong firstNonZero = m_loffset < v.m_loffset ? m_loffset : v.m_loffset;
  ulong lastNonZero = m_roffset < v.m_roffset ? m_roffset : v.m_roffset;
  Vector<T> retval = Vector<T>(m_size, firstNonZero, lastNonZero);
  for(ulong i = firstNonZero; i < m_size - lastNonZero; i++)
    retval.at(i) = ((*this)[i] - v[i]);
  return retval;
}

template<class T>
Vector<T>& Vector<T>::operator-=(const Vector& v)
{
  return (*this = *this - v);
}

template<class T>
Vector<T> Vector<T>::operator*(const T& c) const
{
  Vector<T> retval(*this);
  for(ulong i = 0; i < m_size - m_loffset - m_roffset; i++)
  {
    retval.m_data[i] *= c;
  }

  return retval;
}

template<class T>
Vector<T>& Vector<T>::operator*=(const T& c)
{
  return (*this = *this * c);
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& v) const
{
  bool retval = size() == v.size();
  for(ulong i = 0; i < size() && retval; i++)
    retval = (*this)[i] == v[i];

  return retval;
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& v) const
{
  return !(*this == v);
}

template<class T>
ostream& operator<<(ostream& out, const Vector<T>& rhs)
{
  out << "\n";
  for(ulong i = 0; i < rhs.size(); i++)
    out << rhs[i] << "\t";
  return out;
}

template<class T>
istream& operator>>(istream& in, Vector<T>& rhs)
{
  T temp;
  for(unsigned long i = 0; i < rhs.size(); i++)
  {
    in >> temp;
    if(temp) rhs.at(i) = temp;
  }
  return in;
}

