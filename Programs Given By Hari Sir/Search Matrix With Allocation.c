#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int *allocate_matrix(int n, int m)
{
	int *matrix;
	matrix = (int *)malloc(sizeof(int)*(m*n));
	return matrix;
}

void search(int *arr,int n,int m, int num)
{
	int i = 0, j = m-1;
	while (i < n && j >= 0)
	{
		if (arr[j*m+i] == num)
		{
			printf("found");
			return;
		}
		else
		{
			if (arr[j*m + i] < num)
				i++;
			else
				j--;
		}
	}
	printf("not found");
}

int main()
{
	int num,m,n,*matrix;
	int arr[4][5] = {
			{ 1, 5, 6, 10, 25  },
			{ 2, 6, 7, 12, 27  },
			{ 5, 7, 15, 15, 29 },
			{ 9, 11, 16, 17, 35 }
	};
	printf("enter number of rows::");
	scanf_s("%d", &n);
	printf("enter number of columns::");
	scanf_s("%d", &m);
	matrix = allocate_matrix(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix[j*m + i] = arr[i][j];
	printf("enter element to search::");
	scanf_s("%d", &num);
	search(matrix, n, m, num);
	_getch();
	return 0;
}