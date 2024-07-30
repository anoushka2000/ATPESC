#include <omp.h>
#include <stdio.h>
int main ()  
{
  #pragma omp parallel /* parallel region with default number of threads*/
  {
    printf("Hello");
    printf("World \n");
  }
}
