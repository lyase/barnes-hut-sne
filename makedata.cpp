/** \file  makedata.cpp
*small app to create t-sne data files
compiles with g++ -g -Wall makedata.cpp -o makedata -O3 -I./CBLAS/include -L./ -lblas
*idea make few random points no_pointinball in random unit ball placed in  in cube[0,1]dim 20.
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
#include "tsnelib/quadtree.h"
#include "tsnelib/vptree.h"
#include "tsnelib/tsne.h"
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free */
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <time.h>       /* time */
#include <stdio.h>
#include <time.h>
#include <ctime>
extern "C" {
#include <cblas.h>
}
using namespace std;
/*psuedo random depending on time */
int random_number(int min_num, int max_num)
{   std::clock_t    start;
    start = std::clock();
//    srand (1000000*time(NULL)); /* will change once per sec*/
    srand(start);
    double f = (double)rand() / RAND_MAX; /* if you like [0,1] double */
    int ires=(int)( min_num + f *(max_num - min_num));/* converted to int in range*/

    return ires;
}
double vectorNorm(double* vector,int no_dims)
{
    double norm=0.0;
    for(int dn=0; dn<no_dims ; dn++) {
        norm=norm+ vector[dn]* vector[dn];//
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
    int  no_pointinball=50,  no_dims = 20, no_balls = 4;
    int N = no_balls*no_pointinball ;/*total number of points in set each has *no_dims values*/
    double *data = (double*) calloc(N, sizeof(double));

    for(int bn=0; bn<no_balls ; bn++) {
        // generating the center point of miniball in dim=20.
        int rnd=random_number(1,100);
        double dist= ((double) random_number(1,100))/100.0;// ramdom number [0,1]
        double* ballcenter;
        if ( NULL == (ballcenter = (double*) calloc(no_dims , sizeof(double)))) {
            printf("malloc failed\n");
            return(-1);
        };
        double norm=0.0;

        for(int dn=0; dn<no_dims ; dn++) {

            ballcenter[dn]= ((double) random_number(1,100))/100.0;// ramdom number [0,1]
        }
        // normalize vector to  dist
        normalizeVector(ballcenter,dist,no_dims);
        for(int pointnumber=0; pointnumber<no_pointinball; pointnumber++) {
            double pointdist=((double) random_number(1,100))/100.0;// ramdom number [0,1]
            double* inballpointdirection = (double*) calloc(no_dims , sizeof(double));
            if(inballpointdirection == NULL) {
                printf(" Memory allocation failedcan not create inballpointdirection!\n");
                exit(1);
            }

            for(int dn=0; dn<no_dims ; dn++) {
                inballpointdirection[dn]= ((double)random_number(1,100))/100.0;// ramdom number [0,1]

            }
            normalizeVector( inballpointdirection,pointdist,no_dims);
            for(int dn=0; dn<no_dims ; dn++) {
                data[pointnumber+bn*no_pointinball+dn]=ballcenter[dn]+inballpointdirection[dn];// ramdom number [0,1]
//                data[pointnumber+bn*no_pointinball+dn]=pointnumber+bn*no_pointinball+dn;// static data

            }
// no need to free calloc?            free(inballpointdirection);
        }//for each point  loop
//no need to free calloc?        free(ballcenter);
        // generate ball arround center with good number of points
        //put points in data

    } //for each ball loop
    TSNE* tsne = new TSNE();
    int* landmarks = (int*) malloc(N * sizeof(int));
    if(landmarks == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for(int n = 0; n < N; n++) landmarks[n] = n;
    double* Y = (double*) malloc(N * no_dims * sizeof(double));
    double* costs = (double*) calloc(N, sizeof(double));
    if(Y == NULL || costs == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // save  the parameters and the dataset my save function
//     _save_data(data,no_balls*no_pointinball,no_dims);
    tsne->save_data("data.dat",Y, landmarks, costs, N, no_dims);
//tsne->save_data(data, landmarks, costs, N, no_dims);
//    tsne->save_data("result.dat",Y, landmarks, costs, N, no_dims);
//ave_data(double*, int*, double*, int, int)
// to read 	if(tsne->save_data(&data, &origN, &D, &theta, &perplexity)) {
//return 0;}
    delete(tsne);
//calloc not free ?    free(data);
    free(Y);
//calloc is not freed    free(costs);
    free(landmarks);
}
