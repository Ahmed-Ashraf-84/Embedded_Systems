/*
 ============================================================================
 Name        : ex__3.c
 Author      : ahmed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
void read_array(int **ptr,int row, int col);
void trans_array(int **ptr,int row, int col);
void print_array(int **ptr,int row, int col);

int main(void) {
	int row=0 ,col=0;
	int **ptr=NULL;

	printf("Enter rows and column of matrix :");
	fflush(stdin);
	fflush(stdout);
	scanf("%d",&row);
	scanf("%d",&col);

	ptr = (int **) malloc(row*sizeof(int *));

	if(ptr != NULL)
	{
		int i=0;
		for(i=0;i<row;i++)
		{
			ptr[i] = (int *) malloc(col*sizeof(int));
		}

		read_array(ptr,row,col);
		printf("Entered Matrix : \n");
		print_array(ptr,row,col);
		printf("Transpose of Matrix : \n");
		trans_array(ptr,row,col);

	}




	return EXIT_SUCCESS;
}

void read_array(int **ptr,int row, int col)
{
	int i=0, j=0;

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("Enter element [%d,%d]:",i+1,j+1);
			fflush(stdin);
			fflush(stdout);
			scanf("%d",&ptr[i][j]);


		}


	}

}
void print_array(int **ptr,int row, int col)
{
	int i=0, j=0;

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%d\t",ptr[i][j]);

		}

		printf("\n");
	}

}

void trans_array(int **ptr,int row, int col)
{
	int i=0, j=0;

	for(i=0;i<col;i++)
	{
		for(j=0;j<row;j++)
		{
			printf("%d\t",ptr[j][i]);

		}

		printf("\n");
	}

}
