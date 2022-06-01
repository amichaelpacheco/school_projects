/*
 Michael Pacheco
 4.4.2022
 CS241L-006 Bruna, Jacobson
 
 Project 5 modify sars-cov-2's spike protein
 codons by deletion and mutation with commands
 and create a linked list for the sequence
 
 extra credit +5: handle all possible command line errors
 
 use dynamic arrays for command line args
 1. command line arguments 
 2. get data from file
 3. apply changes
 4. print changes in format
 
 to do list
 despite receiving the correct info to delete a node
 and 3 nodes are deleted, our deleted changes do not match
 
 I printed the replaced codons, but they don't correspond with
 what was printed in the final stage, and the codon 3 previous spaces
 seem to be what are supposed to be replaced
 
 the printed format needs to be fixed for the last amount
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*struct for link in linked codon list*/
struct codonNode
{
	char codon;
	struct codonNode* next;
};

struct codonNode* createNode(char c);
void mutateNode(struct codonNode* current, char newCodon);
void printSequence(struct codonNode* head,char *variantName, int totalCodonCount);
void deleteNode(struct codonNode* current);
void deleteHead(struct codonNode* head);
struct codonNode* searchNode(struct codonNode* head, long codonPosition, 
struct codonNode* current);
void freeList(struct codonNode* head);

int main(int argc, char *argv[])
{
	/*Declaring necessary variables*/
	char c;
	struct codonNode* head = NULL;
	struct codonNode* current = NULL;
	char *ptr;
	int i;
	char **modifications = NULL;
	char *variantName = NULL;
	int deleteCount = 0;
	int totalCodonCount = 1;
	
	/*Fetch command line args*/
	/*============================================================*/
  /*Get variant name*/
	variantName = malloc(strlen(argv[1])+1);
	strcpy(variantName, argv[1]);
	
	/*Get all modification commands of codon sequence*/
	modifications = malloc((argc-2)*sizeof(char *));
	for(i=2;i<argc;i++)
	{
		modifications[i-2] = malloc(strlen(argv[i])+1*sizeof(char *));
		strcpy(modifications[i-2], argv[i]);
	}
	/*============================================================*/
  
	/*Create linked list of protein sequence from stdin*/
	/*============================================================*/
	head = createNode(c=getchar());
	current = head;
	current->next = createNode(c=getchar());
  while((c=getchar()) != EOF)
  {
		if(c != '\n')
		{
		current = current->next;
		current->next = createNode(c);
		totalCodonCount++;
		}
  }
	/*============================================================*/

	/*Perform modifications on linked list/protein sequence*/
	/*============================================================*/
	for(i=0;i<argc-2;i++)
	{
		char first = modifications[i][0];
		modifications[i][0] = ' ';
		
		/*if first char is uppercase we mutate a node*/
		if(isupper(first))
		{
			long codonPosition = strtol(modifications[i],&ptr,10);
			char newCodon = modifications[i][strlen(modifications[i]) - 1];
			current = searchNode(head,codonPosition-deleteCount, current);
			mutateNode(current, newCodon);
		}
		/*if first char is not uppercase we delete a node*/
		else
		{
			long codonPosition = strtol(modifications[i],&ptr,10);
			current = searchNode(head,codonPosition-deleteCount-1, current);
			if(codonPosition == 1)
			{
				deleteHead(head);
			}
			else
			{
				deleteNode(current);
			}
			deleteCount++;
		}
	}
	/*============================================================*/
	
	/*Print modified protein sequence*/
	/*=============================================================*/
	totalCodonCount -= 2;
	printSequence(head, variantName, totalCodonCount);
	/*=============================================================*/
	
	/*Kill data leaks*/
	/*============================================================*/
	/*Free variant name*/
	free(variantName);
	/*Free commands*/
	for(i=0;i<argc-2;i++)
	{
		free(modifications[i]);
	}
	free(modifications);
	/*Free linked list*/
	freeList(head);
	/*============================================================*/
  return 0;
}

/*append linked list, given node data*/
struct codonNode* createNode(char c)
{
	struct codonNode* node = malloc(sizeof(struct codonNode));
	
	node->codon=c;
	node->next=NULL;
	
	return node;
}

/*finds index of codon node*/
struct codonNode* searchNode(struct codonNode* head, 
long codonPosition, struct codonNode* current)
{
	int codonCount = 1;
	int codonPositionLocal = (int) codonPosition;
  current = head;
	while(current != NULL)
	{
	  if(codonCount==codonPositionLocal)
	  {
	    break;
	  }
	  codonCount++;
	  current = current->next;
	}
	return current;
}

/*mutate codon node*/
void mutateNode(struct codonNode* current, char newCodon)
{
	current->codon = newCodon;
}

/*Delete codon node*/
void deleteNode(struct codonNode* current)
{
	struct codonNode* newNode = NULL;
	
	newNode = current->next;
	current->next = newNode->next;
	newNode->next = NULL;
	
	free(newNode);
}
/*Delete codon head of linked list*/
void deleteHead(struct codonNode* head)
{
	struct codonNode* node = head;
	head = node->next;
	free(node);
}

/*print formated spike protein sequence*/
void printSequence(struct codonNode* head,
char *variantName, int totalCodonCount)
{
	struct codonNode* current = head;
	int codonCount = 51;
	int missingCodon = 0;
	int i = 50;
	int j = 0;
	/*we need to get the distance from the next 
	%50 on the last line*/
	while((totalCodonCount + missingCodon)%50 != 0)
	{
		missingCodon++;
	}
	/*print initial lines*/
	printf("Protein sequence for %s:\n", variantName);
	printf("%10d %10d %10d %10d %10d\n", 10, 20, 30, 40, 50);
	while(current != NULL)
	{
		printf("%c", current->codon);
		/*print formatted codon data*/
		if(codonCount%10 == 0)
		{
			printf(" ");
		}
		/*Print formatted codon count*/
		if(codonCount%50 == 0 && codonCount != totalCodonCount+missingCodon)
		{
			i = codonCount;
			printf("\n");
			printf("%10d %10d %10d %10d %10d\n", i-40, i-30, i-20, i-10, i);
		}
		/*print the last line in format*/
		if(codonCount == totalCodonCount+missingCodon)
		{
			printf("\n");
			j = totalCodonCount-(40-missingCodon);
			while(j!=totalCodonCount+10)
			{
				printf("%10d ", j);
				j+=10;
			}
			printf("\n");
		}
		/*move to next node*/
		codonCount++;
		current = current->next;
	}
}

/*Clear the linked list form memory*/
void freeList(struct codonNode* head)
{
	struct codonNode* tmp;
	/*traverse and remove previous node from new head*/
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}