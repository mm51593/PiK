#include <stdio.h>
#include <omp.h>

int main()
{
	long NSTEPS  = 100000000;
	double delta = (double)1 / NSTEPS;
	double pi_sum = 0;

	for (int i = 0; i < NSTEPS; i++)
	{
		double f_val = 4 / (1 + (delta * i) * (delta * i));
		double s = f_val * delta;
		pi_sum += s;
	}

	printf("Pi (serial) = %f\n", pi_sum);
	return 0;
}
