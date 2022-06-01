#ifndef HEADER_FILE
#define HEADER_FILE

int checkRight(int matrix[], int n, int i);
int checkDown(int matrix[], int n, int i);
void printPath(int path[], int n, int matrix[]);
void freeData(int path[], int matrix[]);
void savePosition(int *previousPosn,int *i,
int path[], int matrix[]);
void blockPositions(int *i, int path[], int matrix[]);
void moveToPrevious(int *previousPosn,int *i, int path[]);
int checkNoPath(int matrix[], int n, int i);
void setInitConditions(int *i, int *total, int path[]);
#endif