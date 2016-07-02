#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void printParenthesis(char *str,int position, int n, int open_count, int close_count)
{
	if (close_count == n)
	{
		str[position] = '\0';
		puts(str);
	}
	else
	{
		if (open_count > close_count) 
		{
			str[position] = '}';
			printParenthesis(str,position + 1, n, open_count, close_count + 1);
		}
		if (open_count < n) 
		{
			str[position] = '{';
			printParenthesis(str,position + 1, n, open_count + 1, close_count);
		}
	}
}

int main()
{
	int n;
	char *str;
	printf("enter n value::");
	scanf("%d", &n);
	str = (char *)malloc(n);
	printParenthesis(str, 0, n, 0, 0);
	fflush(stdin);
	getchar();
	return 0;
}