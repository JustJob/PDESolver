//Justin O'Brien
//CS328 Assignment 6
//Instructor: Clayton Price
//Date: 02/25/2013
//This file defines the InvalidIndex class and operators which are friends of it

#ifndef INVALID_INDEX_H
#define INVALID_INDEX_H

#include <iostream>
using namespace std;

class InvalidIndex
{
private:
  short m_index;
public:
  //PRE: None
  //POST: Creates an InvalidIndex object and stores the index that the object
  // was created because of
  InvalidIndex(const short p_index);
  friend ostream& operator<<(ostream& out, const InvalidIndex& rhs);
};

//PRE: None
//POST: outputs into out the InvalidIndex object and lists the index the object
// contains
ostream& operator<<(ostream& out, const InvalidIndex& rhs);

#endif