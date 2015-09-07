#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX_THREADS 16
#define SIZE 20000000

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

/** --- STUDENT STARTUP CODE
        double total = 0.0;
        for (i=0; i<SIZE; i++) {
            total += a[i];
        }            
**/

// --- SOLUTION
        double total = 0.0;
        #pragma omp parallel 
        {
            double my_sum=0.0;
            #pragma omp for
            for (i=0; i<SIZE; i++) {
                my_sum += a[i];
            }   
            #pragma omp critical
            total +=  my_sum;
        }
// --- END SOLUTION

        run_time = omp_get_wtime() - start_time;
        printf("%f %f %d\n",total, run_time,j);
    }
}