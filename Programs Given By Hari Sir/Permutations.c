#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void print_permutation(char *input, int beg,int end)
{
	if (beg==end-1)
		puts(input);
	for (int index = beg; index < end; index++)
	{
		swap(&input[beg], &input[index]);
		print_permutation(input, beg + 1, end);
		swap(&input[beg], &input[index]);
	}
}

int main()
{
	char input[10];
	printf("enter your string::");
	gets_s(input);
	print_permutation(input,0, strlen(input));
	getchar();
	return 0;
}