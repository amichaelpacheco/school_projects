/*
 Michael Pacheco
 5.4.2022
 CS241L-006 Bruna, Jacobson
 
 Project 7 - create a priority queue
 for patients that arrive at a hospital
 based on criteria
 
 highest pain 10 first
 
 patients with highest pain if tie older
 
 if same pain and age earliest time
 
 if time becomes greater than 2hrs they 
 become top priority
 
 things to keep in mind
 patients are only seen every 15 minutes
 
 find priority queue then match to next 15 minute time
 subtract seenAtTime from 15 minute time then assign
 to wait time and replace time with current 15 minute time
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


int main(int argc, char *argv[])
{
	
	/*create needed variables and data structs*/
	char *inputFile = argv[1];
	char *outputFile = argv[2];
	struct patient temp;
	struct patient *patientTable;
	int patientCount = countPatients(outputFile);
	patientTable = malloc(patientCount*sizeof(struct patient));
	/*struct patient patientTable[patientCount];*/
	printf("%d", patientCount);
	/*fill patient table with arrivals.log*/
	fillPatientTable(patientTable, patientCount, inputFile);
	
	/*sort patients in priority queue*/
	queuePatients(patientTable, patientCount, temp);
	
	/*print patient list to mylist.txt in order of seen time*/
	storeSortedTable(patientTable, patientCount, outputFile);
  free(patientTable);
	return 0;
}