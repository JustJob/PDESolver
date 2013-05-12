//Justin O'Brien and Matt Martin
//CS328 Final Project
//Instructor: Clayton Price
//Date: 02/25/2013
//This file defines the InvalidMatrix class and operators which are 
//friends of it
#ifndef INVALID_MATRIX_H
#define INVALID_MATRIX_H

#include <iostream>
#include <string.h>
using namespace std;

class InvalidMatrix
{
private:
  char* m_message;
public:
  //PRE: p_message cannot be null, and should be a message containing location
  // information that cannot be any longer than 100 characters
  //POST: creates a InvalidMatrix object and stores p_message
  InvalidMatrix(const char* p_message);
  friend ostream& operator<<(ostream& out, const InvalidMatrix& rhs);
};

//PRE: None
//POST: outputs this InvalidMatrix object and displays its message
ostream& operator<<(ostream& out, const InvalidMatrix& rhs);

#endif