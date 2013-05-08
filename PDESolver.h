// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file declares the PDESolver class.

#ifndef PDE_SOLVER
#define PDE_SOLVER

#include "vector.h"
#include "BaseMatrix.h"
#include "InvalidMatrix.h"
#include "InvalidBound.h"

template<class T, T lFunc(T), T rFunc(T), T bFunc(T), T tFunc(T), T force(T,T)>
class PDESolver
{
public:
  //PRE: lBound should be less than rBound and bBound should be less than 
  // tBound
  //POST: constructs a pdesolver object and also solves the partial differential
  // equation and stores it in m_A and m_B
  PDESolver(const ulong size, const T lBound, const T rBound,
            const T bBound, const T tBound);
  //PRE: None
  //POST: resizes the size of the mesh for the partial differential equation
  void resize(const ulong size);
  //PRE: None
  //POST: gets the A matrix used for the partial differential equation
  const SymMatrix<T>& getA() const;
  //PRE: None
  //POST: gets the B matrix created for the partial differential equation
  const Vector<T>& getB() const;
  //PRE: operator() must be defined on class U
  //POST: solves the PDE using the operator() of class U. Creates a solution
  // and stores that solution in m_sol
  template<class U>
  const Vector<T> solve() const;
private:
  //PRE: None
  //POST: generates the b vector
  void generateB();
  //PRE: None
  //POST generates the a matrix
  void generateA();
  SymMatrix<T> m_A; //m_A stores the symetric A matrix used to solve this PDE
  Vector<T> m_B; //m_B stores the b vector in the Ax=b equation
  ulong m_size; //the number of points between the bounds of the problem
                //(m_size - 1)^2 is the size of the matrix and solution vector
  T m_leftBound; //the left bound of the problem
  T m_rightBound; //the right bound of the problem
  T m_upperBound; //upper bound of the problem
  T m_lowerBound; //lower bound of the problem
};

#include "PDESolver.hpp"

#endif
