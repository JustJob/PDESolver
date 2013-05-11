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
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

//PDESolver is used to solve a partial differential equation using bounding 
//functions and a forcing function. These functions are passed to as template 
// parameters to PDESolver. 
//  -lFunc is the left bounding function for the space
//  -rFunc is the right bounding function for the space
//  -tFunc is the top bounding function for the space
//  -bFunc is the bottom bounding function for the space
//  -force is the forcing function defined on x and y
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
  //PRE: None
  //POST: creates 5 files that output data in a way that they can create a 3D
  // graph in GNUPlot. The sol vector should be an ouput of the solve function
  // and it will be formatted correctly so that data points show up in the 
  // correct position on the graph
  void gnuPlotify(Vector<T>& sol,const string &method);

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
