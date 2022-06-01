#include <stdio.h>
#include <stdlib.h>
#include "header.h"
/*sets patients appointment seen time from arrival time and adds wait time*/
void setPatientSeenTime(struct patient patientTable[], int i, int currentTime)
{
	/*patient wait time is the current time - patient arrival time*/
	patientTable[i].waitTime = currentTime - patientTable[i].time;
	/*set patient time as the appointment time for printing*/
	patientTable[i].time = currentTime;
}

/*counts number of patients in log file*/
int countPatients(char *inputFile)
{
	int patientCount = 0;
	FILE *fp;
	char c;
	/*open file pointer*/
	fp = fopen(inputFile, "r");
	if(fp==NULL)
	{
		printf("failed to open the file");
		exit(0);
	}
	/*count patients*/
	while((c=fgetc(fp)) != EOF)
	{
		if(c == '\n')
		{
			patientCount++;
		}
	}
	/*close file pointer*/
	fclose(fp);
	return patientCount;
}

/*stores patients in struct table*/
void fillPatientTable(struct patient patientTable[], int patientCount, char *inputFile)
{
	FILE *fp;
	int hour;
	int minute;
	int second;
	char colon1;
	char colon2;
	int i;
	
	/*open file pointer*/
	fp = fopen(inputFile, "r");
	if(fp==NULL)
	{
		printf("failed to open the file");
		exit(0);
	}
	/*get information*/
	for(i=0;i<patientCount;i++)
	{
		/*break fscanf into 3 parts
		so we can convert the arrival time into seconds*/
		fscanf(fp, "%d %d%c%d%c%d %d %d", 
		&patientTable[i].id, 
		&hour, &colon1, &minute, &colon2, &second,
		&patientTable[i].age,
		&patientTable[i].painLevel);
		/*convert all time to seconds*/
		patientTable[i].time = ((hour*3600)+(minute*60)+second);
		patientTable[i].waitTime = 0;
	}
	/*close file pointer*/
	fclose(fp);
}

int checkPriorityPatient(struct patient patientTable[], 
int currentPriority, int i, int currentTime)
{
	int twoHrs = 7200;
	patientTable[i].waitTime = (currentTime-patientTable[i].time);
	patientTable[currentPriority].waitTime = (currentTime-patientTable[currentPriority].time);
	
	if((currentTime-patientTable[i].time)<twoHrs &&
	(currentTime-patientTable[currentPriority].time)<twoHrs)
	{
		if(patientTable[i].painLevel == 10)
		{
			return i;
		}
		if(patientTable[currentPriority].painLevel == 10)
		{
			return currentPriority;
		}
		if(patientTable[i].painLevel < 10)
		{
			if(patientTable[i].painLevel > 
			patientTable[currentPriority].painLevel)
			{
				return i;
			}
			else if(patientTable[i].painLevel < 
			patientTable[currentPriority].painLevel)
			{
				return currentPriority;
			}
			/*if the pain level is the same check the other criteria*/
			else if(patientTable[i].painLevel == 
			patientTable[currentPriority].painLevel)
			{
				/*pioritize oldest patient*/
				if(patientTable[i].age > 
				patientTable[currentPriority].age)
				{
					return i;
				}
				else if(patientTable[i].age < 
				patientTable[currentPriority].age)
				{
					return currentPriority;
				}
				else if(patientTable[i].age == 
				patientTable[currentPriority].age)
				{
					if(patientTable[i].time < 
					patientTable[currentPriority].time)
					{
						return i;
					}
					else if(patientTable[i].time > 
					patientTable[currentPriority].time)
					{
						return currentPriority;
					}
					else
					{
						return currentPriority;
					}
				}
				else
				{
					return currentPriority;
				}
			}
		}
	}
	else
	{
		if((currentTime-patientTable[i].time)>
		(currentTime-patientTable[currentPriority].time) && 
		patientTable[currentPriority].painLevel != 10)
		{
			return i;
		}
		if((currentTime-patientTable[i].time)<
		(currentTime-patientTable[currentPriority].time) && 
		patientTable[i].painLevel != 10)
		{
			return currentPriority;
		}
		if(patientTable[currentPriority].painLevel == 10)
		{
			return currentPriority;
		}
		if(patientTable[i].painLevel == 10)
		{
			return i;
		}
		else
		{
			return currentPriority;
		}
	}
	return currentPriority;
}

/*queues patients with priority criteria*/
void queuePatients(struct patient patientTable[], int patientCount, struct patient temp)
{
	int i = 0;
	int currentPriority = 0;
	int previous = 0;
	int fifteenMinutes = 900;
	/*current time is 7:45 in seconds*/
	int currentTime = 27900;
	
	/*check if we have finished queuing*/
	while(previous != patientCount)
	{
		while(currentTime > patientTable[i].time &&
		i!=patientCount-1)
		{
			currentPriority = checkPriorityPatient(patientTable, currentPriority, i, currentTime);
			
			/*move to the next patient*/
			i++;
		}
		/*move to get next priority patient*/
		setPatientSeenTime(patientTable, currentPriority, currentTime);
		temp = patientTable[previous];
		patientTable[previous] = patientTable[currentPriority];
		patientTable[currentPriority] = temp;
		
		/*add 15 min*/
		currentTime += fifteenMinutes;
		/*move to next appointment*/
		previous++;
		/*set variables to check next priority of patients*/
		currentPriority=previous;
		i=previous;
	}
}

/*stores queued patient table into txt file*/
void storeSortedTable(struct patient patientTable[], int patientCount, char *outputFile)
{
	FILE *fp;
	int i;
	int arrivalHr;
	int arrivalMin;
	int arrivalSec;
	int waitHr;
	int waitMin;
	int waitSec;
	
	/*open file pointer*/
	fp = fopen(outputFile, "w+");
	if(fp==NULL)
	{
		printf("failed to open the file");
		exit(0);
	}
	/*write patient table*/
	for(i=0;i<patientCount;i++)
	{
		/*get stringable times*/
		/*convert seen time to stringable format*/
		arrivalHr = patientTable[i].time/3600;
		arrivalMin = (patientTable[i].time-(arrivalHr*3600))/60;
		arrivalSec =  (patientTable[i].time-(arrivalHr*3600))-(arrivalMin*60);
		/*convert wait time to stringable format*/
		waitHr = patientTable[i].waitTime/3600;
		waitMin = (patientTable[i].waitTime-(waitHr*3600))/60;
		waitSec = (patientTable[i].waitTime-(waitHr*3600))-(waitMin*60);
		
		/*print to text file*/
		fprintf(fp, 
		"%02d:%02d:%02d Patient: ID = %d, Pain Level (1-10) = %d, Age = %d years, Time waiting = %02dh%02dm%02ds\n",
		arrivalHr, arrivalMin, arrivalSec, 
		patientTable[i].id, 
		patientTable[i].painLevel, 
		patientTable[i].age, 
		waitHr, waitMin, waitSec);
	}
	/*close file pointer*/
	fclose(fp);
}
