/*
 Michael Pacheco
 4.23.2022
 CS241L-006 Bruna, Jacobson
 
 Project 6 - given a 2d array 
 find a path through 0s and 1s
 by only moving right and down
 
 notes:
 I didn't create functions for 
 
 single lines of code

 variable declarations
 
 dynamic mem allocation
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

int main(int argc, char *argv[])
{
	/*declare necessary variables*/
	int i = 0;
	int n = 0;
	int total = 1;
	int *matrix;
	int *path;
	int previousPosn = 0;
	int c;
	
	matrix = (int*)malloc((1000)*sizeof(int));
	/*continue populating matrix*/
	while((c=getchar()) != '\n')
	{
		matrix[i] = c-'0';
		n++;
		i++;
	}
	/*realloc for n*/
	matrix = (int*)realloc(matrix, ((n*n)*sizeof(int)));
	while((c=getchar()) != EOF)
	{
		if(c != '\n')
		{
			matrix[i] = c-'0';
			/*printf(" %d", matrix[i]);*/
			i++;
		}
	}
	
	/*get size of n var*/
	total = n*n;

	
	/*calloc path array so all variables are 
	set to zero*/
	path = (int*)calloc((n*n), sizeof(int));
	
	/*set initial conditions of path and matrix*/
	setInitConditions(&i, &total, path);
	
	/*run pathfinding*/
	while(i != (n*n)-1)
	{
		/*do we save current posn before or after moving?
		will it interfere*/
		/*check right */
		if(checkRight(matrix, n, i))
		{
			/*save current position and previous position*/
			savePosition(&previousPosn, &i, path, matrix);
			
			/*move to new posn*/
			i++;
		}
		/*check down */
		else if(checkDown(matrix, n, i))
		{
			/*save current position and previous position*/
			savePosition(&previousPosn, &i, path, matrix);
			
			/*move to new posn*/
			i = i+n;
		}
		/*backtrack*/
		else
		{
			/*delete current posn from path soln*/
			/*set current posn as blocked in matrix*/
			blockPositions(&i, path, matrix);
			
			/*move to previous position*/
			moveToPrevious(&previousPosn, &i, path);
			
			/*if we backtrack to first node
			and all other paths are blocked, 
			no path*/
			if(checkNoPath(matrix, n, i))
			{
				printf("no path found.\n");
				freeData(path, matrix);
				exit(0);
			}
		}
	}
	/*print the found results*/
	printPath(path, n, matrix);
	/*free matrix & path arrays*/
	freeData(path, matrix);
  return 0;
}
