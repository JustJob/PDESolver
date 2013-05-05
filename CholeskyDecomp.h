// Justin O'Brien
// cs328 hw6
// 4/2/2013

// This file declares the Choleski Decomposition class.

#ifndef CHOLESKY_DECOMP_H
#define CHOLESKY_DECOMP_H

#include "SymMatrix.h"
#include "UpperTriangular.h"
#include "LowerTriangular.h"
#include "Vector.h"

template <class T>
class CholeskyDecomp
{
public:
  //PRE: m's rows should be the size of sol
  //POST: solves for x in mx=sol using cholesky decomposition
  Vector<T> operator()(const SymMatrix<T>& m, const Vector<T>& sol) const;
};

#include "CholeskyDecomp.hpp"

#endif