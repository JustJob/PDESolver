//Justin O'Brien and Matt Martin
//CS328 Final Project
//Instructor: Clayton Price
//Date: 02/25/2013
//This file declares the InvalidBound class and operators which are 
//friends of it
#include "InvalidBound.h"

InvalidBound::InvalidBound(const char* p_message) 
{
  m_message = new char[100];
  strcpy(m_message, p_message);
}

ostream& operator<<(ostream& out, const InvalidBound& rhs)
{
  out << "Invalid Matrix Usage: " << rhs.m_message;
  return out;
}