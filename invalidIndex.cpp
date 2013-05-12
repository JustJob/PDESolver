//Justin O'Brien and Matt Martin
//CS328 Final Project
//Instructor: Clayton Price
//Date: 02/25/2013
//This file declares the InvalidIndex class and operators which are 
//friends of it
#include "invalidIndex.h"

InvalidIndex::InvalidIndex(const short p_index) : m_index(p_index) {}

ostream& operator<<(ostream& out, const InvalidIndex& rhs)
{
  out << "Error trying to access index: " << rhs.m_index;
  return out;
}