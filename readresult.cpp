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
#include<iostream>
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
#include <cblas.h>
#include <iomanip>      // std::setprecision

int main()
{
    // Define some variables 2= dimension for lower space projection ?
    int origN, N, D, no_dims = 2, *landmarks;
    double perc_landmarks;
    double perplexity, theta, *data;

    TSNE* tsne = new TSNE();

    // Read the parameters and the dataset
    if(tsne->load_data("data.dat",&data, &origN, &D, &theta, &perplexity)) {
        std::cout<<"done reading dataset\n"<<"got "<<origN<<"records\n";
        std::cout<<"theta:"<<theta<<"\n";
        std::cout<<"perplexity:"<<perplexity<<"\n";
    }
    for(int i=0; i<origN; i++) {
        cout<<"data["<<i<<"]="<<std::fixed<<setprecision(5)<<data[i]<<endl;
    }
    delete(tsne);
    free(data);

    return 0;
}
