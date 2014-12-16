/** \file  makedata.cpp
*small app to create t-sne data files
compiles with g++ -g -Wall makedata.cpp -o makedata -O3 -I./CBLAS/include -L./ -lblas
*idea make few regularly placed balls in cube[0,1]dim 20.
*generate random data in each of these balls.
*run bh_tsne
*plot the reults in 2 dim without labels
*add labels see it is helps
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



extern "C" {
#include <cblas.h>
}


using namespace std;

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
int random_number(int min_num, int max_num)
 {
     int result=0,low_num=0,hi_num=0;
     if(min_num<max_num)
     {
         low_num=min_num;
         hi_num=max_num+1; // this is done to include max_num in output.
     }else{
         low_num=max_num+1;// this is done to include max_num in output.
         hi_num=min_num;
     }
     srand(time(NULL));
     result = (rand()%(hi_num-low_num))+low_num;
     return result;
 }

int main()
{
     // Define some variables
     int  N=500,  no_dims = 2000  ;
     //Random numbers
     srand(time(NULL));
     int r = rand();
     int c1= random_number(1,10);
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
