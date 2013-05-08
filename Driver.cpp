// Justin O'Brien
// cs328 hw5
// 4/2/2013

// This file runs a driver that is used to test the matrix class.

#include "Driver.h"
#include <string>
using namespace std;


int main(int argc, char** argv)
{
  VectorMathTest();
  MatrixEqualityTest();
  DenseMatrixMathTest();

  if(argc < 2)
  {
    cout << "No command entered (ts for timeseries and axb to solve..." << endl;
    return 0;
  }
  if(strcmp(argv[1], "ts") == 0)
  {
    short dataPnts;
    if(argc < 3)
    {
      cout << "No max size parameter entered. Enter one now: ";
      cin >> dataPnts;
    }
    else
    {
      dataPnts = atoi(argv[2]);
    }
    generateTimeComparison(dataPnts);
  }
  else if(strcmp(argv[1], "axb") == 0)
  {
    if(argc < 4)
    {
      cout << "Not enough parameters to solve PDE, need mesh size and method" 
           << endl;
      exit(0);
    }
    //if(strcmp(argv[4])
  
    myPDE solver(atoi(argv[2]), 0, 1, 0, 1);
    Vector<double> solution = solver.solve<CholeskyDecomp<double> >();
    solver.gnuPlotify(solution,string("Cholesky"));
  }

  return 0;
}

double getTime()
{
  timeval now;
  gettimeofday(&now, NULL);
  return ((double)now.tv_usec)/1000000 + now.tv_sec;
}

void generateTimeComparison(short max)
{
  ofstream out("timeAnal.csv");
  out << "Size,Method,Time" << endl;
  double start;
  for(short i = 3; i <= max; i++)
  {
    myPDE solver1(i, 0, 1, 0, 1);
    myPDE solver2(i, 0, 1, 0, 1);
    cout << i << endl;

    start = getTime();
    solver1.solve<CholeskyDecomp<double> >();
    out << i << ",CholeskyDecomp," << getTime() - start << endl;

    start = getTime();
    solver2.solve<GaussSeidel<double> >();
    out << i << ",GaussSeidel," << getTime() - start << endl;
  }
}

double right(double x)
{
  return 1;
}
double left(double x)
{
  return 0;
}
double upper(double x)
{
  return x * x * x;
}
double lower(double x)
{
  return x * x * x;
}
double forcingFunc(double x, double y)
{
  return y;
}

void VectorMathTest()
{
  int data[] = {1,2,3};
  Vector<int> v1(5,1,1);
  Vector<int> v2(5,0,2);
  Vector<int> v3(5);
  for(ulong i = 0; i < 3; i++)
  {
    v1.at(i+1) = data[i];
    v2.at(i) = data[i];
    v3.at(i) = data[i];
  }
  v3.at(3) = 9;
  v3.at(4) = 3;

  assert(0 == v1[0]);
  assert(v2[3] == 0);
  assert(v2[4] == 0);
  try
  {
    v1.at(0) = 2;
    assert(false);
  }
  catch(InvalidIndex& e) {}
  try
  {
    v2.at(3) = 2;
    assert(false);
  }
  catch(InvalidIndex& e) {}
  try
  {
    v1.at(4) = 2;
    assert(false);
  }
  catch(InvalidIndex& e) {}
  Vector<int> v4(5, 0, 1);
  v4.at(0) = 1;
  v4.at(1) = 3;
  v4.at(2) = 5;
  v4.at(3) = 3;
  assert(v4 == v1 + v2);

  v4 = Vector<int>(5);
  v4.at(0) = 1;
  v4.at(1) = 3;
  v4.at(2) = 5;
  v4.at(3) = 3;
  v4.at(4) = 0;
  assert(v4 == v1 + v2);
  try
  {
    (v1+v2).at(4) = 2;
    assert(false);
  }
  catch(InvalidIndex& e) {}

  assert(v1 * v2 ==  8);
  assert(v1 * v3 == 35);
  assert(v2 * v3 == 14);

  assert(v1.mag() == (int)sqrt(14));
  assert(v2.mag() == (int)sqrt(14));
  assert(v3.mag() == (int)sqrt(104));

  Vector<int> v5(v2);
  v2 += v1;
  v2.at(0) = 1; //shouldn't throw
  try
  {
    v2.at(4) = 2;
    assert(false);
  }
  catch(InvalidIndex& e) {}
  assert(v5 == v2 - v1);
  v1 += v3;
  v1.at(0) = 1; //shouldn't throw exception
}

void MatrixEqualityTest()
{
  Matrix<int> a1(3,3);
  Matrix<int> b1(3,3);
  BaseMatrix<int>& a = a1;
  BaseMatrix<int>& b = b1;
  assert(a==b);
  a.at(0, 0) = 1;
  a.at(0, 1) = 2;
  a.at(0, 2) = 3;
  a.at(1, 0) = 4;
  a.at(1, 1) = 5;
  a.at(1, 2) = 6;
  a.at(2, 0) = 7;
  a.at(2, 1) = 8;
  a.at(2, 2) = 9;
  assert(a!=b);
  b.at(0, 0) = 1;
  b.at(0, 1) = 2;
  b.at(0, 2) = 3;
  b.at(1, 0) = 4;
  b.at(1, 1) = 5;
  b.at(1, 2) = 6;
  b.at(2, 0) = 7;
  b.at(2, 1) = 8;
  assert(a!=b);
  b.at(2, 2) = 9;
  assert(a==b);
  b = a;
  assert(a==b);
}

void DenseMatrixMathTest()
{
  Matrix<int> a1(3,3);
  Matrix<int> b1(3,3);
  Matrix<int> c1(3,3);
  Matrix<int> d1(3,3);
  BaseMatrix<int>& a = a1;
  BaseMatrix<int>& b = b1;
  BaseMatrix<int>& c = c1;
  BaseMatrix<int>& d = d1;
  a.at(0, 0) = 1;
  a.at(0, 1) = 2;
  a.at(0, 2) = 3;
  a.at(1, 0) = 4;
  a.at(1, 1) = 5;
  a.at(1, 2) = 6;
  a.at(2, 0) = 7;
  a.at(2, 1) = 8;
  a.at(2, 2) = 9;
  b.at(0, 0) = 0;
  b.at(0, 1) = 1;
  b.at(0, 2) = 2;
  b.at(1, 0) = 1;
  b.at(1, 1) = 0;
  b.at(1, 2) = 1;
  b.at(2, 0) = -1;
  b.at(2, 1) = 0;
  b.at(2, 2) = 0;
  c.at(0, 0) = -1;
  c.at(0, 1) = 1;
  c.at(0, 2) = 4;
  c.at(1, 0) = -1;
  c.at(1, 1) = 4;
  c.at(1, 2) = 13;
  c.at(2, 0) = -1;
  c.at(2, 1) = 7;
  c.at(2, 2) = 22;
  d.at(0, 0) = 2;
  d.at(0, 1) = 4;
  d.at(0, 2) = 6;
  d.at(1, 0) = 8;
  d.at(1, 1) = 10;
  d.at(1, 2) = 12;
  d.at(2, 0) = 14;
  d.at(2, 1) = 16;
  d.at(2, 2) = 18;
  a1*b1;
  assert(c==a1*b1);
  assert(d==a1*2);
  c = a;
  a += b;
  a -= b;
  assert(a==c);
  Vector<int> e(3), f(3);
  e.at(0) = 1;
  e.at(1) = 4;
  e.at(2) = 5;
  f.at(0) = 24;
  f.at(1) = 54;
  f.at(2) = 84;
  assert(f == a*e);

  a1 = Matrix<int>(2,3);
  b1 = Matrix<int>(3,2);
  assert((a1*b1).numCols() == 2 && (b1*a1).numCols() == 3);

  UpperTriangular<int> ut1(3);
  ut1.at(0,0) = 1;
  ut1.at(0,1) = 2;
  ut1.at(0,2) = 3;
  ut1.at(1,1) = 4;
  ut1.at(1,2) = 5;
  ut1.at(2,2) = 6;
  UpperTriangular<int> ut2(3);
  ut2.at(0,0) = 1;
  ut2.at(0,1) = 10;
  ut2.at(0,2) = 31;
  ut2.at(1,1) = 16;
  ut2.at(1,2) = 50;
  ut2.at(2,2) = 36;
  assert(ut1 * ut1 == ut2);

  LowerTriangular<int> lt1(3);
  lt1.at(0,0) = 1;
  lt1.at(1,0) = 2;
  lt1.at(2,0) = 4;
  lt1.at(1,1) = 3;
  lt1.at(2,1) = 5;
  lt1.at(2,2) = 6;
  LowerTriangular<int> lt2(3);
  lt2.at(0,0) = 1;
  lt2.at(1,0) = 8;
  lt2.at(2,0) = 38;
  lt2.at(1,1) = 9;
  lt2.at(2,1) = 45;
  lt2.at(2,2) = 36;
  assert(lt1 * lt1 == lt2);

  SymMatrix<int> sym1(3);
  sym1.at(1,1) = 4;
  sym1.at(2,1) = -7;
  sym1.at(1,0) = 2;
  sym1.at(2,2) = 1;
  sym1.at(0,0) = -1;
  sym1.at(0,2) = 0;
  Matrix<int> test1(3,3);
  test1.at(0,0) = 5;
  test1.at(1,0) = 6;
  test1.at(2,0) = -14;
  test1.at(0,1) = 6;
  test1.at(1,1) = 69;
  test1.at(2,1) = -35;
  test1.at(0,2) = -14;
  test1.at(1,2) = -35;
  test1.at(2,2) = 50;
  assert(sym1*sym1 == test1);
}
