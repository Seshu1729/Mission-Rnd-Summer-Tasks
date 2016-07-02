#include <stdio.h>
#include <stdlib.h>

void search(int arr[5][5], int num)
{
	int i = 0, j = 0;
	while (1)
	{
		if (arr[i][j] == num)
		{
			printf("found");
			break;
		}
		else
		{
			if (arr[i][j] < num)
				i++;
			else
				j--;
		}
	}
}

int main()
{
	int num;
	int arr[5][5] = {
			{ 1, 5, 6, 10, 25  },
			{ 2, 6, 7, 12, 27  },
			{ 5, 7, 15, 15, 29 },
			{ 9, 11, 16, 17, 35 },
			{ 15, 17, 29, 32, 34 }
	};
	printf("enter element to search::");
	scanf_s("%d", &num);
	search(arr, num);
	return 0;
}