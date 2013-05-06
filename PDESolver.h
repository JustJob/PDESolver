// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file declares the PDESolver class.

#ifndef PDE_SOLVER
#define PDE_SOLVER

#include "Vector.h"
#include "Matrix.h"
#include "VectorNorm.h"
#include "InvalidMatrix.h"
#include <cmath>

const float EQUAL_THRESHOLD = 0.000001;

template<class T, double lFunc(double), double rFunc(double), 
         double bFunc(double), double tFunc(double)>
class PDESolver
{
public:
  PDESolver(const ulong size = 0, const T lBound, const T rBound,
            const T tBound, const T bBound);
  void resize(const ulong size);
  const SymMatrix<T>& getA() const;
  const Vector<T>& getB() const;
  template<class U>
  const BaseMatrix<T>& solve<U>() const;
private:
  void generateB();
  void generateA();
  SymMatrix<T> m_A;
  Vector<T> m_B;
  Vector<T> m_sol;
  ulong m_size;
  bool m_solved;
  T m_leftBound;
  T m_rightBound;
  T m_upperBound;
  T m_lowerBound; 
};

#include "PDESolver.hpp"

#endif
