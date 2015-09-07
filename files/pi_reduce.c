/**
  Based on Tim Mattons' tutorial at Intel
  https://software.intel.com/en-us/courseware/249662
**/

#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 32

static long num_steps = 100000000;
double step;
int main ()
{
    int i,j;
    double pi, full_sum = 0.0;
    double start_time, run_time;

    step = 1.0/(double) num_steps;

    printf("pi secs nthreads\n");

    j=4;

    for (j=1;j<=MAX_THREADS ;j++) {
        omp_set_num_threads(j);
        full_sum=0.0;
        start_time = omp_get_wtime();

        // --- TU CODIGO AQUI
        // ----- SOLUCION ----
        #pragma omp parallel for reduction(+:full_sum)
        for (i=0; i<num_steps; i++) {
                double x = (i+0.5)*step;
                full_sum = full_sum + 4.0/(1.0+x*x);
        }
        pi = step * full_sum;
        // --- FIN SOLUCION ----

        run_time = omp_get_wtime() - start_time;
        printf("%f %f %d\n",pi,run_time,j);
    }
}