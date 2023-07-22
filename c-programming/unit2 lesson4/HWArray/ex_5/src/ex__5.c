/*
 ============================================================================
 Name        : ex__5.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int n=0,elm=0;
	int *ptr=NULL;
	printf("Enter number of elements :");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&n);
	ptr =(int *) calloc(n,sizeof(int));

	if(ptr != NULL)
		{
			int i=0;
			for(i=0;i < n+1 ; i++)
			{
				ptr[i]= 11*(i+1);

			}

			for(i=0;i<(n);i++)
			{
				printf("%d\t",ptr[i]);
			}

			printf("\nEnter the element to be searched: ");
			fflush(stdin);
			fflush(stdout);
			scanf("%d",&elm);

			for(i=0;i<n;i++)
			{
				if(ptr[i]==elm)
				{
					break;
				}


			}
			if(i==n)
			{
				printf("Number NOT found ");
			}
			else
			{
				printf("Number found at location:%d ",i+1);
			}



		}
	return EXIT_SUCCESS;
}
