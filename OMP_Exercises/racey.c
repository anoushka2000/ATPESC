
#include <stdio.h>
#include <omp.h>

int main()
{

  printf("I think");
  #pragma omp parallel

  #pragma omp single // workshare construct
  // single thread creates tasks and puts them on a queue
  {
    #pragma omp task // a random thread picks the task and does it
    printf(" car");

    #pragma omp task // a random thread picks the task and does it
    printf(" race");
  } // implicit barrier

  printf("s are fun\n");

}
