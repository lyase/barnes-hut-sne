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
     if(min_num<max_num) {
          low_num=min_num;
          hi_num=max_num+1; // this is done to include max_num in output.
     } else {
          low_num=max_num+1;// this is done to include max_num in output.
          hi_num=min_num;
     }
     srand(time(NULL));
     result = (rand()%(hi_num-low_num))+low_num;
     return result;
}
double vectorNorm(double* vector,int no_dims)
{
     double norm=0.0;
     for(int dn=0; dn<no_dims ; dn++) {
          norm=norm+ vector[dn]* vector[dn];// ramdom number [0,1]
     }
     return norm;
}
void normalizeVector( double * vector, double dist, int no_dims )
{
     double norm=0.0;
     norm=vectorNorm(vector,no_dims);
     for(int dn=0; dn<no_dims ; dn++) {

          vector[dn]= vector[dn]*dist / sqrt(norm);// ramdom number [0,1]
     }
}
int main()
{
     // Define some variables
     int  no_pointinball=5000,  no_dims = 20, no_balls = 100;
     double *data = (double*) calloc(no_balls*no_pointinball * no_dims, sizeof(double));

     //Random numbers
     srand(time(NULL));
     int r = rand();
     int dist= random_number(1,10)/10;// ramdom number [0,1]
     for(int bn=0; bn<no_balls ; bn++) {
          // generating the center of miniball in dim=20.
          int dist= random_number(1,10000)/10000;// ramdom number [0,1]
          double* ballcenter = (double*) calloc(no_dims , sizeof(double));
          double norm=0.0;

          for(int dn=0; dn<no_dims ; dn++) {

               ballcenter[dn]= random_number(1,10000)/10000;// ramdom number [0,1]
          }
          // normilze vector to  dist
          normalizeVector(ballcenter,dist,no_dims);
          for(int pointnumber=0; pointnumber<no_pointinball; pointnumber++) {
               int pointdist= random_number(1,10000)/10000;// ramdom number [0,1]
               double* inballpointdirection = (double*) calloc(no_dims , sizeof(double));


               for(int dn=0; dn<no_dims ; dn++) {
                    inballpointdirection[dn]= random_number(1,10000)/10000;// ramdom number [0,1]
               }
               normalizeVector( inballpointdirection,pointdist,no_dims);
               for(int dn=0; dn<no_dims ; dn++) {
                    data[pointnumber+bn*no_pointinball+dn]=inballpointdirection[dn]+ballcenter[dn];// ramdom number [0,1]
                    //           data[pointnumber+bn*no_pointinball+dn]=pointnumber+bn*no_pointinball+dn;// static data

               }
               free(inballpointdirection);
          }
          free(ballcenter);
          // generate ball arround center with good number of points
          //put points in data

     }
//for loop
     TSNE* tsne = new TSNE();

     // save  the parameters and the dataset
     _save_data(data,no_balls*no_pointinball,no_dims);
//not easy to use     tsne->save_data(data, landmarks, costs, N, no_dims);
//ave_data(double*, int*, double*, int, int)

// to read 	if(tsne->save_data(&data, &origN, &D, &theta, &perplexity)) {
//return 0;}
     delete(tsne);
     free(data);
}
