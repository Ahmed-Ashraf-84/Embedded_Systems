/*
 ============================================================================
 Name        : ex__1.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
void get_array(float arr[][2]);
void print_array(float arr[][2]);
void add_array(float arr1[][2],float arr2[][2],float sum[][2]);

int main(void) {

	float a[2][2]={0},b[2][2]={0},c[2][2]={0};

	printf("Enter the elements of 1st matrix \n");
	get_array(a);

	printf("Enter the elements of 2nd matrix \n");
	get_array(b);

	add_array(a,b,c);
	printf("sum of matrix : \n");
	print_array(c);

	return EXIT_SUCCESS;
}
void get_array(float arr[][2])
{
	int i=0,j=0;
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("Enter element [%d,%d] :",i+1,j+1);
			fflush(stdout);
			fflush(stdin);
			scanf("%f",&arr[i][j]);
			fflush(stdout);
			fflush(stdin);
		}


	}
}

void print_array(float arr[][2])
{
	int i=0,j=0;
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%0.2f\t",arr[i][j]);


		}

		printf("\n");
	}
}
void add_array(float arr1[][2],float arr2[][2],float sum[][2])
{
	int i=0,j=0;
		for(i=0;i<2;i++)
		{
			for(j=0;j<2;j++)
			{
				sum[i][j] = arr1[i][j] + arr2[i][j] ;


			}


		}

}
