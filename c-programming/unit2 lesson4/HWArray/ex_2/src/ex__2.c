/*
 ============================================================================
 Name        : ex__2.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
void read_array(float arr[], int length);
float avg(float *arr,int length);

int main(void) {

	int n=0;
	float *ptr=NULL;
	printf("Enter number of elemnts :");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&n);

	ptr=(float *) malloc(n*sizeof(float));
	if(ptr != NULL)
	{
		float avg_value=0;
		read_array(ptr,n);
		avg_value = avg(ptr,n);
		printf("Average :%0.2f",avg_value);
	}

	return EXIT_SUCCESS;
}
void read_array(float *arr, int length)
{
	int i =0;
	for(i=0;i<length;i++)
	{
		printf("Enter number [%d]:",i+1);
		fflush(stdout);
		fflush(stdin);
		scanf("%f",&arr[i]);

	}

}

float avg(float *arr,int length)
{
	int i =0;
	float sum=0;
	for(i=0;i<length;i++)
	{
		sum += arr[i];

	}

	return (sum/length);
}
