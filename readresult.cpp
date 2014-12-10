/** \file  makedata.cpp
*small app to create t-sne data files
compiles with g++ -g -Wall makedata.cpp -o makedata -O3 -I./CBLAS/include -L./ -lblas

*\n
*then run with
*\code  ./test \endcode
 *\version  1.0
 *\date 01/05/12 10:06:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *\author:  lyase.d, lyase.d@gmail.com
 *        Company:
 *
 * =====================================================================================
 */
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include "quadtree.h"
#include "vptree.h"
#include "tsne.h"
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */
#include <cblas.h>

void _save_data(double* data, int n, int d)
{
     // Open file, write first 2 integers number of records number of dim of each record and then the data
     FILE *h;
     if((h = fopen("data.dat", "w+b")) == NULL) {
          printf("Error: could not open data file.\n");
          return;
     }
     fwrite(&n, sizeof(int), 1, h);//write number of records
     fwrite(&d, sizeof(int), 1, h);// write number of dimmension
     fwrite(data, sizeof(double), n * d, h);
     fclose(h);
     printf("Wrote the %i x %i data matrix successfully!\n", n, d);
}
void _read_results(double* data, int n, int d)
{
     // Open file, write first 2 integers number of records number of dim of each record and then the data
     FILE *h;
     if((h = fopen("result.dat", "w+b")) == NULL) {
          printf("Error: could not open data file.\n");
          return;
     }

     if(tsne->load_data(&data, &origN, &D, &theta, &perplexity)) {
     fwrite(&n, sizeof(int), 1, h);//write number of records
     fwrite(&d, sizeof(int), 1, h);// write number of dimmension
     fwrite(data, sizeof(double), n * d, h);
     fclose(h);
     printf("Wrote the %i x %i data matrix successfully!\n", n, d);
}
int main()
{
     // Define some variables
     int  N=5000,  no_dims = 2000  ;

     double *data = (double*) calloc(no_dims * N, sizeof(double));
     for(int ii=0; ii<no_dims *N; ii++) {
          data[ii]=ii;
     }
//for loop
     TSNE* tsne = new TSNE();

     // save  the parameters and the dataset
     _save_data(data,N,no_dims);
//not easy to use     tsne->save_data(data, landmarks, costs, N, no_dims);
//ave_data(double*, int*, double*, int, int)

// to read 	if(tsne->save_data(&data, &origN, &D, &theta, &perplexity)) {
//return 0;}
     delete(tsne);
}
