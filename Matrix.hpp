// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file implements the matrix class.

template<class T>
Matrix<T>::Matrix(const BaseMatrix<T>& rhs)
{
  data = NULL;
  (*this) = rhs;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
  data = NULL;
  (*this) = rhs;
}

template<class T>
Matrix<T>::Matrix(unsigned long row, unsigned long col) :m_rows(row),m_cols(col)
{
  if(!(row && col))
    throw InvalidMatrix("Matrix with 0 rows or 0 columns");

  data = new Vector<T>[row];
  for(unsigned long i = 0; i < row; i++)
  {
    data[i] = Vector<T>(col);
    for(unsigned long j = 0; j < col; j++)
      data[i].at(j) = 0;
  }
}

template<class T>
Matrix<T>::~Matrix()
{
  if(data) delete [] data;
}

template<class T>
T& Matrix<T>::at(unsigned long row, unsigned long col)
{
  if(row >= numRows())
    throw InvalidIndex(row);
  return data[row].at(col);
}

template<class T>
const T& Matrix<T>::operator()(unsigned long row, unsigned long col) const
{
  if(row >= numRows())
    throw InvalidIndex(row);
  return data[row][col];
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const BaseMatrix<T>& rhs)
{
  return *this = *this * rhs;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const BaseMatrix<T>& rhs) const
{
  if(numCols() != rhs.numRows())
    throw InvalidVectorMath("Trying to multiply two incompatable matrices");

  Matrix<T> retval(numRows(), rhs.numCols());
  for(unsigned long i = 0; i < numRows(); i++)
    for(unsigned long j = 0; j < rhs.numCols(); j++)
      retval.at(i,j) = getRow(i) * rhs.getCol(j);
  return retval;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& c)
{
  for(unsigned long i = 0; i < numRows(); i++)
    data[i] *= c;
  return (*this);
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const BaseMatrix<T>& rhs)
{
  for(unsigned long i = 0; i < numRows(); i++)
    data[i] += rhs.getRow(i);
  return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const BaseMatrix<T>& rhs)
{
  for(unsigned long i = 0; i < numRows(); i++)
    data[i] -= rhs.getRow(i);
  return *this;
}

template<class T>
Matrix<T>& Matrix<T>::transpose()
{
  Vector<T>* temp = new Vector<T>[numCols()];
  Matrix<T> retval(*this);
  for(unsigned long i = 0; i < numRows(); i++)
      temp[i] = getCol(i);
  if(data) delete [] data;
  data = temp;
  return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
  return operator=((BaseMatrix<T>&)rhs);
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const BaseMatrix<T>& rhs)
{
  m_rows = rhs.numRows();
  m_cols = rhs.numCols();
  if(data) delete [] data;
  data = new Vector<T>[numRows()];
  for(unsigned long i = 0; i < numRows(); i++)
  {
    data[i] = rhs.getRow(i);
  }
  return *this;
}

template<class T>
unsigned long Matrix<T>::numRows() const
{
  return m_rows;
}
template<class T>
unsigned long Matrix<T>::numCols() const
{
  return m_cols;
}

template<class T>
Vector<T>& Matrix<T>::getRow(unsigned long i) const
{
  if(i >= m_rows)
    throw InvalidIndex(i);
  return data[i];
}

template<class T>
Vector<T> Matrix<T>::getCol(unsigned long i) const
{
  if(i >= m_cols)
    throw InvalidIndex(i);

  Vector<T> retval(m_rows);

  for(unsigned long j = 0; j < m_rows; j++)
    retval.at(j) = (*this)(j, i);
  return retval;
}

template<class T>
bool operator==(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs)
{
  bool equal = rhs.numRows() == lhs.numRows() && rhs.numCols() == lhs.numCols();
  for(unsigned long i = 0; i < lhs.numRows() && equal; i++)
    for(unsigned long j = 0; j < lhs.numCols() && equal; j++)
      if(lhs(i, j) != rhs(i, j))
        equal = false;

  return equal;
}

template<class T>
bool operator!=(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs)
{
  return !(lhs == rhs);
}

template<class T>
ostream& operator<<(ostream& out, const BaseMatrix<T>& rhs)
{
  out << "\n";
  for(unsigned long i = 0; i < rhs.numRows(); i++)
  {
    for(unsigned long j = 0; j < rhs.numCols(); j++)
      out << rhs(i, j) << "\t";
    out << "\n";
  }
  return out;
}

template<class T>
istream& operator>>(istream& in, BaseMatrix<T>& rhs)
{
  T temp;
  for(unsigned long i = 0; i < rhs.numRows(); i++)
    for(unsigned long j = 0; j < rhs.numCols(); j++)
    {
      in >> temp;
      if(temp)
        rhs.at(i,j) = temp;
    }

  return in;
}

template<class T>
Vector<T> operator*(const BaseMatrix<T>& lhs, const Vector<T>& rhs)
{
  if(lhs.numCols() != rhs.size())
    throw InvalidVectorMath("Trying to multiply a matrix by a \
      vector of different sizes");
  Vector<T> retval(lhs.numRows());
  for(unsigned long i = 0; i < lhs.numRows(); i++)
    retval.at(i) = lhs.getRow(i) * rhs;
  return retval;
}

template<class T>
Matrix<T> operator*(const BaseMatrix<T>& lhs, const T& c)
{
  Matrix<T> retval(lhs);
  return retval *= c;
}

template<class T>
Matrix<T> operator+(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs)
{
  Matrix<T> retval(lhs);
  return retval += rhs;
}

template<class T>
Matrix<T> operator-(const BaseMatrix<T>& lhs, const BaseMatrix<T>& rhs)
{
  Matrix<T> retval(lhs);
  return retval -= rhs;
}

