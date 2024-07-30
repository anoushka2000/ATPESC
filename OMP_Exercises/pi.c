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
int main ()
{
	double pi, sum = 0.0;
	double start_time, run_time;
	int nthrds = 20;
	// double sum_array[nthrds];
	int max_threads = omp_get_max_threads();
	printf("\n max_threads %ld", max_threads);

	step = 1.0/(double) num_steps;
	start_time = omp_get_wtime();
	// export OMP_NUM_THREADS=nthrds;
	// omp_set_num_threads(nthrds); /* runtime function to request a certain number of threads */
	#pragma omp parallel /* parallel region with default number of threads */
	{	
		// nthrds = omp_get_num_threads();
		int ID = omp_get_thread_num();
		int thread_steps = num_steps/nthrds;
		double local_sum = 0.0;
		double x;

		int start = ID*thread_steps + 1;
		int end = start + thread_steps;
		printf("\n ID %ld \n start %ld \n end %ld \n", ID, start, end);

		if (ID == nthrds-1) {
			end = num_steps;
		}

		for (int i=start;i<end; i++){
			x = (i-0.5)*step;
			local_sum = local_sum + 4.0/(1.0+x*x);
	  	}
		
		#pragma omp critical
		sum += local_sum;
	}

	// for (int j=0;j<= nthrds; j++){

	// 	sum += sum_array[j];
	// 	printf("\n j %ld \n sum %lf", j, sum);
	// }

	printf("\n nthrds %ld \n ", nthrds);
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  





