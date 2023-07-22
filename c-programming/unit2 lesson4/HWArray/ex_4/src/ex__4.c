/*
 ============================================================================
 Name        : ex__4.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int n=0,elm=0,loc=0;
	int *ptr=NULL;
	printf("Enter number of elements :");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&n);
	ptr =(int *) calloc((n+1),sizeof(int));

	if(ptr != NULL)
	{
		int i=0;
		printf("Enter the element to be inserted: ");
		fflush(stdin);
		fflush(stdout);
		scanf("%d",&elm);
		printf("Enter the location: ");
		fflush(stdin);
		fflush(stdout);
		scanf("%d",&loc);

		for(i=n;i != (loc-1);i--)
		{
			ptr[i]=ptr[i-1];

		}

		ptr[loc-1]=elm;

		for(i=0;i<(n+1);i++)
		{
			printf("%d\t",ptr[i]);
		}

	}


	return EXIT_SUCCESS;
}

