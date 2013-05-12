//Justin O'Brien and Matt Martin
//CS328 Final Project
//Instructor: Clayton Price
//Date: 02/25/2013
//This file declares the InvalidVectorMath class and operators which are 
//friends of it
#include "InvalidVectorMath.h"

InvalidVectorMath::InvalidVectorMath(const char* p_message) 
{
  strcpy(m_message, p_message);
}

ostream& operator<<(ostream& out, const InvalidVectorMath& rhs)
{
  out << "Invalid Vector Math: " << rhs.m_message;
  return out;
}