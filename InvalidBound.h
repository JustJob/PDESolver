//Justin O'Brien
//CS328 Assignment 6
//Instructor: Clayton Price
//Date: 02/25/2013
//This file defines the InvalidBound class and operators which are 
//friends of it
#ifndef INVALID_BOUND_H
#define INVALID_BOUND_H

#include <iostream>
#include <string.h>
using namespace std;

class InvalidBound
{
private:
  char* m_message;
public:
  //PRE: p_message cannot be null, and should be a message containing a message
  // about the incorrect bounds
  //POST: creates a InvalidBound object and stores p_message
  InvalidBound(const char* p_message);
  friend ostream& operator<<(ostream& out, const InvalidBound& rhs);
};

//PRE: None
//POST: outputs this InvalidBound object and displays its message
ostream& operator<<(ostream& out, const InvalidBound& rhs);

#endif