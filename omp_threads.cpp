#include<iostream>
#include<omp.h>


int main(void)
{
	int N = 100, result = 0;
	#pragma omp parallel for reduction(+:result)
	for (int i = 0; i < N; i++)
	{
		std::cout << omp_get_thread_num() << std::endl;
		for (int j = 0; j < N; j++)
		{
			std::cout << j << std::endl;
			result += j;
		}
	}

	std::cout << result;
	return 0;
}
