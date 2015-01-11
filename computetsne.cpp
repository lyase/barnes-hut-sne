
/*
 *  tsne.cpp
 *  Implementation of both standard and Barnes-Hut-SNE.
 *
 *  Created by Laurens van der Maaten.
 *  Copyright 2012, Delft University of Technology. All rights reserved.
 *
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

extern "C" {
#include <cblas.h>
}


using namespace std;
// Function that runs the Barnes-Hut implementation of t-SNE
int main()
{

    // Define some variables 2= dimension for lower space projection ?
    int origN, N, D, no_dims = 2, *landmarks;
    double perc_landmarks;
    double perplexity, theta, *data;
    TSNE* tsne = new TSNE();

    // Read the parameters and the dataset
    if(tsne->load_data("data.dat",&data, &origN, &D, &theta, &perplexity)) {

        // Make dummy landmarks
        N = origN;
        int* landmarks = (int*) malloc(N * sizeof(int));
        if(landmarks == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        for(int n = 0; n < N; n++) landmarks[n] = n;

        // Now fire up the SNE implementation
        double* Y = (double*) malloc(N * no_dims * sizeof(double));
        double* costs = (double*) calloc(N, sizeof(double));
        if(Y == NULL || costs == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
        perplexity=6.0;
        theta=0.0;
        tsne->run(data, N, D, Y, no_dims, perplexity, theta);

        // Save the results
        tsne->save_data("result.dat",Y, landmarks, costs, N, no_dims);

        // Clean up the memory
        free(data);
        data = NULL;
        free(Y);
        Y = NULL;
        free(costs);
        costs = NULL;
        free(landmarks);
        landmarks = NULL;
    }
    delete(tsne);
}

