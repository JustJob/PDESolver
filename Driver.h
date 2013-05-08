// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file declares a few test functions for the matrix class

#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include "Matrix.h"
#include "UpperTriangular.h"
#include "LowerTriangular.h"
#include "SymMatrix.h"
#include "CholeskyDecomp.h"
#include "GaussSeidel.h"
#include "vector.h"
#include "PDESolver.h"
#include <assert.h>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
using namespace std;

//PRE: None
//POST: Checks a few assertions to make sure that the == and != operators work
// for the matrix class
void MatrixEqualityTest();

//PRE: None
//POST: Checks the +, -, and 3 types of * operations for matrices and make sure
// they are correct
void DenseMatrixMathTest();

//PRE: None
//POST: runs some math tests on different types of matrices
void VectorMathTest();

double upper(double x);
double lower(double x);
double right(double x);
double left(double x);
double forcingFunc(double x, double y);
double getTime();
void generateTimeComparison(short max);

typedef PDESolver<double, left, right, lower, upper, forcingFunc> myPDE;

#endif
