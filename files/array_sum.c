#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define MAX_THREADS 10
#define SIZE 10000000
#define ATYPE double

int main ()
{
    
    ATYPE *a = (ATYPE *)malloc(sizeof(ATYPE)*SIZE);
    ATYPE *c = (ATYPE *)malloc(sizeof(ATYPE)*SIZE);
    int i,j;
    double start_time, run_time1, run_time2, run_time3, run_time4, run_time5;

    printf("secs1 secs2 secs3 secs4 secs5 nthreads\n");

    for (j=1;j<=MAX_THREADS ;j++) {
        omp_set_num_threads(j);
        ATYPE x = 12;

        for (i=0; i<SIZE; i++) {
            c[i] = 2;
            a[i] = 10;
        }

        start_time = omp_get_wtime();
        #pragma omp parallel for private(x)
        for (i=0; i<SIZE; i++) x = 10*i;
        run_time1 = omp_get_wtime() - start_time;

        start_time = omp_get_wtime();
        #pragma omp parallel for private(x)
        for (i=0; i<SIZE; i++) x = c[i]*10;
        run_time2 = omp_get_wtime() - start_time;

        start_time = omp_get_wtime();
        #pragma omp parallel for  private(x)
        for (i=0; i<SIZE; i++) c[i] = c[i]*x;
        run_time4 = omp_get_wtime() - start_time;

        start_time = omp_get_wtime();
        #pragma omp parallel for private(x)
        for (i=0; i<SIZE; i++) c[i] = a[i]*x;
        run_time5 = omp_get_wtime() - start_time;

        start_time = omp_get_wtime();
        #pragma omp parallel for  private(x)
        for (i=0; i<SIZE; i++) c[i]=x;
        run_time3 = omp_get_wtime() - start_time;

        printf("%f %f %f %f %f %d\n", run_time1,run_time2, run_time3, run_time4, run_time5, j);
    } 
}