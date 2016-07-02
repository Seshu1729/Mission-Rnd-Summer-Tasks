#include <stdio.h>

void merge(int arr[], int beg, int mid, int end)
{
	int i = beg, j = mid + 1, index = beg, temp[1001], k;
	while ((i <= mid) && (j <= end))
	{
		if (arr[i]<arr[j])
			temp[index++] = arr[i++];
		else
			temp[index++] = arr[j++];
	}
	if (i>mid)
	{
		while (j <= end)
			temp[index++] = arr[j++];
	}
	else
	{
		while (i <= mid)
			temp[index++] = arr[i++];
	}
	for (k = beg; k<index; k++)
		arr[k] = temp[k];
}

void merge_sort(int arr[], int beg, int end)
{
	if (beg<end)
	{
		int mid = (beg + end) / 2;
		merge_sort(arr, beg, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, beg, mid, end);
	}
}

int main()
{
	int arr[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	for (int index = 0; index < 10; index++)
		printf("%d ", arr[index]);
	printf("\n");
	merge_sort(arr,0, 9);
	for (int index = 0; index < 10; index++)
		printf("%d ", arr[index]);
	getchar();
}