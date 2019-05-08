#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
static long num_steps = 1000000;
double step;
int main ()
{
	step=1.0/(double) num_steps;
	double ini = omp_get_wtime();
	for(int j=0; j<NUM_THREADS; j++){
		omp_set_num_threads(j);
		double pi=0.0;
	#pragma omp parallel
	{
		int i, id, nthreads;
		double x, sum=0.0;
		id=omp_get_thread_num();
		nthreads=omp_get_num_threads();
		for(i=id, sum=0.0; i<num_steps; i+=nthreads){
			x=(i+0.5)*step;
			sum+=4.0/(1+x*x);
		}
		#pragma omp critical
		pi+=sum*step;
	}
	printf("The value of pi = %f, num_of_threads = %d, time =%f \n", pi, j+1, omp_get_wtime()-ini);
	}
}