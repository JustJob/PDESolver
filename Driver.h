// Justin O'Brien and Matt Martin
// CS328 Final Project
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

//PRE: None
//POST: The upper bound function for the Dirichlet problem we solve
double upper(double x);

//PRE: None
//POST: The lower bound function for the Dirichlet problem we solve
double lower(double x);

//PRE: None
//POST: The right bound function for the Dirichlet problem we solve
double right(double x);

//PRE: None
//POST: The left bound function for the Dirichlet problem we solve
double left(double x);

//PRE: None
//POST: The forcing function for the Dirichlet problem we solve
double forcingFunc(double x, double y);

//PRE: Must be running on a linux system
//POST: Get time uses a linux based time that is accurate to the milliseconds
// This returns time in seconds.
double getTime();

enum Method {BOTH, GS, CHOL}; //used to determine type of axb solver

//PRE: max > 2
//POST: runs the PDE solver solve method on sizes 3...max. It uses the method m
// and uses both methods if m specifies. It then creates a csv file that logs
// the time each function run took
void generateTimeComparison(short max, Method m);

typedef PDESolver<double, left, right, lower, upper, forcingFunc> myPDE;

#endif
