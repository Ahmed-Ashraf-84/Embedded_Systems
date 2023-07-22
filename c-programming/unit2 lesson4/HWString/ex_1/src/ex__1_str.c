/*
 ============================================================================
 Name        : ex__1_str.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char ch=0,i=0;
	int j=0;
	char str[50];

	printf("Enter a string :");
	fflush(stdin);
	fflush(stdout);
	gets(str);
	printf("Enter character to find frequency:");
	fflush(stdin);
	fflush(stdout);
	scanf("%c",&ch);

	while(str[j] !='\0')
	{
		if(str[j] == (char)ch )
		{
			i++;
		}
		j++;

	}

	printf("frequency of %c :%d",ch,i);

	return EXIT_SUCCESS;
}
