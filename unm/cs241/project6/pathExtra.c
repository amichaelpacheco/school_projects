#include <stdio.h>
#include <stdlib.h>

int checkRight(int matrix[], int n, int i)
{
	/*if the next space is open (1) AND
	not out of bounds return true*/
	if(matrix[i+1] == 1 && (i+1)%n != 0)
	{
		return 1;
	}
	return 0;
}
void savePosition(int *previousPosn,int *i, int path[], int matrix[])
{
	/*save current posn, soon to be previous*/
	*previousPosn = *i;
	/*save our current posn to the path matrix*/
	path[*i] = matrix[*i];
}
int checkDown(int matrix[], int n, int i)
{
	/*if the posn down 1 is 1
	AND we do not move to a row greater than the
	n*n matrix total size(out of bounds)*/
	if(matrix[i+n] == 1 && (i-n) < (n*n))
	{
		return 1;
	}
	return 0;
}
int checkNoPath(int matrix[], int n, int i)
{	
	if(i == 0 && 
		checkRight(matrix, n, i) == 0 &&
		checkDown(matrix, n, i) == 0)
	{
		return 1;
	}
	return 0;
}
void moveToPrevious(int *previousPosn,int *i, int path[])
{
	while(path[*previousPosn] != 1)
	{
		(*previousPosn)--;
	}
	*i = *previousPosn;
}
void printPath(int path[], int n)
{
	int i = 0;
	/*print the matrix*/
	printf("PATH FOUND!\n");
	for(i=0;i<(n*n);i++)
	{
		printf("%d", path[i]);
		/*print newline for length of n- col*/
		if((i+1)%n == 0)
		{
			printf("\n");
		}
	}
}
void blockPositions(int *i, int path[], int matrix[])
{
	path[*i] = 0;
	matrix[*i] = 0;
}
void freeData(int path[], int matrix[])
{
	free(path);
	free(matrix);
}
void setInitConditions(int *i, int *total, int path[])
{
	*i = 0;
	path[0] = 1;
	path[(*total)-1] = 1;
}
