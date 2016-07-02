#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
int calculate_power(int base, int power)
{
	int result = 1;
	while (power--)
		result *= base;
	return result;
}

void print_permutation(char *input, int length)
{
	int combinations_count = calculate_power(2, length);
	while (combinations_count--)
	{
		int index = 0;
		for (int i = 1 << length - 1; i > 0; i = i / 2)
			(combinations_count & i) ? printf("%c", input[index++]) : index++;
		printf("\n");
	}
}

int main()
{
	char input[10];
	printf("enter your string::");
	gets_s(input);
	print_permutation(input, strlen(input));
	getchar();
	return 0;
}