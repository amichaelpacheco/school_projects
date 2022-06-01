#ifndef HEADER_FILE
#define HEADER_FILE

struct patient
{	
  int id;	
  int	time;
  int age;
	int painLevel;
	int waitTime;
};


int countPatients(char *inputFile);
void fillPatientTable(struct patient patientTable[], int patientCount, char *inputFile);
void storeSortedTable(struct patient patientTable[], int patientCount, char *outputFile);
void queuePatients(struct patient patientTable[], int patientCount, struct patient temp);


#endif