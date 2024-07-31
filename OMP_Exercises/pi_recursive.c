/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;

double compute_pi (int start, int end, double step_size) {
	printf("\n start %ld end %ld",start,end);
	double sum = 0, sum_1, sum_2;

	if (end-start < 50000) {
		for (int i=start;i<= end; i++){
		double x = (i-0.5)*step_size;
		sum = sum + 4.0/(1.0+x*x);
		}
		return sum;
	}
	int mid = start + (end-start)/2;
	#pragma omp task shared(sum_1)
	sum_1 = compute_pi(start, mid, step);
	#pragma omp task shared(sum_2)
	sum_2 = compute_pi(mid, end, step);
	#pragma omp taskwait
	return  sum_1 + sum_2;
}

int main ()
{
	  double pi, sum = 0;
	  double start_time, run_time;

	  step = 1.0/(double) num_steps;

	  start_time = omp_get_wtime();
	  #pragma omp parallel 
	  {
		#pragma omp single 
			sum = compute_pi (0, num_steps, step);
	  }

	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





