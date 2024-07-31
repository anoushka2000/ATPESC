#include <omp.h>
#include <stdio.h>
int main ()  
{
    double A[1000]; /* shared among all the threads */
    omp_set_num_threads(4); /* runtime function to request a certain number of threads */
    #pragma omp parallel /* parallel region with default number of threads */
    {
        int ID = omp_get_thread_num(); /* thread local */
        int nthrds = omp_get_num_threads();  /* runtime function to return actual number of threads */
        pooh(ID, A); 
    }
    printf("All done\n")
}