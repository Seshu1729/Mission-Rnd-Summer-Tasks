#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximum_sum_subarray(int *input, int length)
{
	int *count_array, sum = 0, result = input[0], i, j;
	count_array = (int *)malloc(sizeof(int)*length);
	for (i = 0; i<length; i++)
	{
		count_array[i] = sum + input[i];
		sum += input[i];
		if (count_array[i]>result)
			result = count_array[i];
	}
	for (i = 1; i<length; i++)
	{
		for (j = i + 1; j<length; j++)
		{
			if (count_array[j] - count_array[i - 1]>result)
				result = count_array[j] - count_array[i - 1];
		}
	}
	return result;
}

int main()
{
	int input[10] = { 2, -4, 1, 2, 3, -5, 0, 6, -2, 1 }, input_size = 10;
	printf("maximum size subarray is :: %d", maximum_sum_subarray(input, input_size));
	getchar();
	return 0;
}
