
/**
  Based on Tim Mattons' tutorial at Intel
  https://software.intel.com/en-us/courseware/249662
**/

#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 4

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

    //  =========== INICIA UN BUCLE DESDE j=1 HASTA MAX_THREADS ============
    omp_set_num_threads(j);
    full_sum=0.0;
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int i;
        int id = omp_get_thread_num();
        int numthreads = omp_get_num_threads();
        double x;

        for (i=id;i< num_steps; i+=numthreads){
            x = (i+0.5)*step;
            full_sum = full_sum + 4.0/(1.0+x*x);
        }
    }

    pi = step * full_sum;
    run_time = omp_get_wtime() - start_time;
    printf("%f %f %d \n",pi,run_time,j);
    //  =========== CIERRA EL BUCLE AQUÍ ============
   }
}