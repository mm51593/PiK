#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 8

int main()
{
	long NSTEPS  = 1000000000;
	double delta = (double)1 / NSTEPS;
	double pi_sum = 0;

	double partial_sum[NUM_THREADS][8];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		partial_sum[i][0] = 0;
	}

	#pragma omp parallel num_threads(NUM_THREADS)
	{
		int thID = omp_get_thread_num();
		for (int i = 0; i < NSTEPS / NUM_THREADS; i++)
		{
			double x = thID * NSTEPS / NUM_THREADS * delta + i * delta;
			double f_val = 4 / (1 + x * x);
			double s = f_val * delta;
			partial_sum[thID][0] += s;
		}
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pi_sum += partial_sum[i][0];
	}

	printf("Broj dretvi: %d\nPi (serial) = %f\n", NUM_THREADS, pi_sum);
	return 0;
}
