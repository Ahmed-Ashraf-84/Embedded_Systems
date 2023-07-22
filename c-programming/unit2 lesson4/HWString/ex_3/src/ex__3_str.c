/*
 ============================================================================
 Name        : ex__3_str.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int j=0;
	char str[50];

	printf("Enter a string :");
	fflush(stdin);
	fflush(stdout);
	gets(str);

	while(str[j] !='\0')
	{
		j++;
	}
	printf("Revers string is :");
	for(--j;j>=0;j--)
	{
		printf("%c",str[j]);
	}




	return EXIT_SUCCESS;
}
