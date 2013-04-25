//Justin O'Brien
//CS328 Assignment 6
//Instructor: ClaytonPrice
//Date: 02/25/2013
//This file defines the InvalidVectorMath class and operators which are 
//friends of it
#ifndef INVALID_VECTOR_MATH_H
#define INVALID_VECTOR_MATH_H

#include <iostream>
#include <string.h>
using namespace std;

class InvalidVectorMath
{
private:
  char* m_message;
public:
  //PRE: p_message cannot be null, and should be a message containing location
  // information
  //POST: creates a dividebyzero object and stores p_message
  InvalidVectorMath(const char* p_message);
  friend ostream& operator<<(ostream& out, const InvalidVectorMath& rhs);
};

//PRE: None
//POST: outputs this dividebyzero object and displays its message
ostream& operator<<(ostream& out, const InvalidVectorMath& rhs);

#endif