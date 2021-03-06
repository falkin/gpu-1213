#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include "rowMajorTools.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * a11 a12 a13
 * a21 a22 a32
 * a31 a32 a33
 *
 * vectoriser
 *
 * [a11 a12 a13 | a21 a22 a32 | a31 a32 a33]
 */
void print(int* ptrA, int n, int m, string titre)
    {
    cout << titre << " (n,m)=(" << n << "," << m << ")" << endl;
    for (int s = 1; s <= n * m; s++)
	{
	cout << *ptrA++ << "\t";
	if (s % m == 0)
	    {
	    cout << endl;
	    }
	}
    }

/**
 * a11 a12 a13
 * a21 a22 a32
 * a31 a32 a33
 *
 * vectoriser
 *
 * [a11 a12 a13 | a21 a22 a32 | a31 a32 a33]
 */
bool isEgale(int* ptrA, int* ptrB, int n, int m)
    {
    for (int s = 1; s <= n * m; s++)
	{
	if (*ptrA != *ptrB)
	    {
	    int i;
	    int j;

	    to2D1(s, i, j,m);

	    cout << "Matrix : isEgale : error : (i,j)=(" << i << "," << j << ")";
	    cout << " : (x1,x2)=(" << *ptrA << "," << *ptrB << ")";
	    cout << " : delta = " << abs(*ptrA != *ptrB) << endl;

	    return false;
	    }
	ptrA++;
	ptrB++;
	}

    return true;
    }

/**
 * s in [1,nm]
 * i in [1,n]
 * j in [1,m]
 */
void to2D1(int s, int& i, int& j,int m)
    {
    to2D0(s, i, j,m);
    i++;
    j++;
    }

/**
 * s in [0,nm-1]
 * i in [0,n-1]
 * j in [0,m-1]
 */
void to2D0(int s, int& i, int& j,int m)
    {
    i = s / m;
    j = s % m;
    }

/**
 * s in [1,nm]
 * i in [1,n]
 * j in [1,m]
 */
void to1D1(int& s,int i,int j,int m)
    {
    to1D0(s,i,j,m);
    s++;
    }

/**
 * s in [0,nm-1]
 * i in [0,n-1]
 * j in [0,m-1]
 */
void to1D0(int& s,int i,int j,int m)
    {
    s=i*m+j;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

