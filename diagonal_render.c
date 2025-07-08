#include<stdio.h>

int main(void)
{
	int n, m;
	printf("n: ");
	scanf("%d", &n);
	printf("m: ");
	scanf("%d", &m);

	int matrix[n][m];

	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			matrix[i][j] = n * j + i;
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n + m - 1; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i - j >= n || j >= m)
			{
				continue;
			}
			printf("%3d ", matrix[i - j][j]);
			//printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
