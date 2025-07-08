#include<stdio.h>
#include<omp.h>


int test = 0;


int main(void)
{    int iter = 400;
    
    #pragma omp parallel for reduction(+:test)
    for (int i = 0; i < iter; i++)
    {
        for (int j = 0; j < iter; j++)
        {
            test++;
        }
        printf("%d\n", omp_get_thread_num());
    }
    
    printf("%d\n", test);
    return 0;
}
