
#ifndef TSNE_H
#define TSNE_H
/* Cmake will define ${LIBRARY_NAME}_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define ${LIBRARY_NAME}_EXPORTS when
building a DLL on windows.
*/
// We are using the Visual Studio Compiler and building Shared libraries

#if defined (_WIN32)
#if defined(examplelib_EXPORTS)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#else
#define DLLEXPORT
#endif
#ifndef SWIG
#include <math.h>
#include <iostream>    // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <queue>
#include <limits>
#include <iostream>
#include <cfloat>
#include <limits>
using namespace std;
#include "quadtree.h"
#include "vptree.h"
extern "C" {
#include <cblas.h>
}
#else
#endif
/*
 *  tsne.h
 *  Header file for t-SNE.
 *
 *  Created by Laurens van der Maaten.
 *  Copyright 2012, Delft University of Technology. All rights reserved.
 *
 */


static inline double sign(double x)
{
    return (x == .0 ? .0 : (x < .0 ? -1.0 : 1.0));
}


class DLLEXPORT TSNE {
public:
    void run(double* X, int N, int D, double* Y, int no_dims, double perplexity, double theta);
    bool load_data(const char * filename,double** data, int* n, int* d, double* theta, double* perplexity);
    void save_data(const char* filename,double* data, int* landmarks, double* costs, int n, int d);

    void symmetrizeMatrix(int** row_P, int** col_P, double** val_P, int N); // should be static?!


private:
    void computeGradient(double* P, int* inp_row_P, int* inp_col_P, double* inp_val_P, double* Y, int N, int D, double* dC, double theta);
    void computeExactGradient(double* P, double* Y, int N, int D, double* dC);
    double evaluateError(double* P, double* Y, int N);
    double evaluateError(int* row_P, int* col_P, double* val_P, double* Y, int N, double theta);
    void zeroMean(double* X, int N, int D);
    void computeGaussianPerplexity(double* X, int N, int D, double* P, double perplexity);
    void computeGaussianPerplexity(double* X, int N, int D, int** _row_P, int** _col_P, double** _val_P, double perplexity, int K);
    void computeGaussianPerplexity(double* X, int N, int D, int** _row_P, int** _col_P, double** _val_P, double perplexity, double threshold);
    void computeSquaredEuclideanDistance(double* X, int N, int D, double* DD);
    double randn();
};
/* the following Math  class is used to test the python wrapper work for basic pointer manipulation*/
class DLLEXPORT Math {
public:
    Math();
    int pi() const;
    void pi(int pi);
private:
    int _pi;
};
int DLLEXPORT fact(int n);

#endif
