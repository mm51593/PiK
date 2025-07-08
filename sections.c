#include<omp.h>
#include<stdio.h>

int main(void)
{
	#pragma omp parallel
	{
		#pragma omp sections nowait
		{
			#pragma omp section
				printf("Section 1\n");

			#pragma omp section
				printf("Section 2\n");

			#pragma omp section
				printf("Section 3\n");
		}
		#pragma omp single
			printf("Sections done\n");
	}
	return 0;
}
