
#include <omp.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    int thread_id;
    int nthreads = omp_get_num_threads();
    printf("Antes de bifurcar el numero total de threads es %d\n", nthreads);

    #pragma omp parallel private(thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("Este es el thread numero %d\n", thread_id);

        if (thread_id == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Este es el thread master, con id %d. El numero total de threads ahora es %d\n", thread_id, nthreads);
        }
    }

    return 0;
}