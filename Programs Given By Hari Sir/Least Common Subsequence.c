#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void largest_common_subsequence(char *input1, int length1, char *input2,int length2)
{
	size_t index1, index2, count, flag;
	for (index1 = 0; index1 < length1; index1++)
	{
		for (index2 = 0; index2 < length2; index2++)
		{
			if (input1[index1] == input2[index2])
			{
				flag = index1;
				break;
			}
		}
	}
}

int main()
{
	char input1[10], input2[10];
	printf("enter string1::");
	fflush(stdin);gets(input1);
	printf("enter string2::");
	fflush(stdin);gets(input2);
	largest_common_subsequence(input1, strlen(input1), input2, strlen(input2));
	return 0;
}