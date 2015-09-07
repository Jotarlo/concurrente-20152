/**
  Based on Tim Mattons' tutorial at Intel
  https://software.intel.com/en-us/courseware/249662
**/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX_THREADS 16
#define SIZE 10000000

int main ()
{
    
    double *a = (double *)malloc(sizeof(double)*SIZE);
    int i,j;
    double start_time, run_time;

    // fill up some values
    for (i=0; i<SIZE; i++) a[i] = 1;

    printf("total secs nthreads\n");

    for (j=1;j<=MAX_THREADS ;j++) {
        omp_set_num_threads(j);
        start_time = omp_get_wtime();


        double total = 0.0;
// --- REMOVE PRAGMA LINE FOR STUDENT
        #pragma omp parallel for reduction(+:total)
        for (i=0; i<SIZE; i++) total += a[i];

        run_time = omp_get_wtime() - start_time;

        printf("%f %f %d\n",total, run_time,j);
    }
}