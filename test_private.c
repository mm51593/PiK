#include<stdio.h>
#include<omp.h>

#define ITER 60

int main(int argc, char*argv[])
{
	long i=5, n=100, m=50;
	#pragma omp parallel for private(i) firstprivate(n) lastprivate(m)
	for (long j=0; j<ITER; j++)
	{
		int thid=omp_get_thread_num();
		i=i+thid;
		n=n+thid;
		m=m+thid;
		#pragma omp critical (printer)
		{
			fprintf(stdout, "Thread%d: j=%ld, i=%ld, n=%ld, m=%ld\n", thid, j, i, n, m);
		}
	}
	printf("-----------------------------------------\n");
	printf("Na kraju: i=%ld, n=%ld, m=%ld\n", i, n, m);
	printf("-----------------------------------------\n");
}
