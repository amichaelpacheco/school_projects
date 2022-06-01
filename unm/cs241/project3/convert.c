/*
 Michael Pacheco
 3.4.2022
 CS241L-006 Bruna, Jacobson
 Project 3 convert: create a modular program that converts the units 
 of	temperature, weight, length, currency, and volume.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printTheResult(float convertFrom, char unitOne[20], 
float result, char unitTwo[20]);

int convert(char name[20], char unitOne[20], 
char unitTwo[20], int selectFunction);

int main(void)
{
  int selectFunction;
  char continueChar;
  char name[20];
  char unitOne[20];
  char unitTwo[20];
  while(1)
  {
	printf("Main menu\n");
    printf("What would you like to convert?\n");
    printf("Enter:");
    scanf(" %d", &selectFunction);
	printf("\n");
    printf("1 - Temperature\n");
    printf("2 - Weight\n");
    printf("3 - Length\n");
    printf("4 - Currency\n");
    printf("5 - Volume\n");
    



    /*Temperature*/
    if(selectFunction == 1)
    {
      strcpy(name,"Temperature");
      strcpy(unitOne,"Celsius");
      strcpy(unitTwo,"Fahrenheit");
      convert(name, unitOne, unitTwo, selectFunction);
    }
    /*Weight*/
    else if(selectFunction == 2)
    {
      strcpy(name,"Weight");
      strcpy(unitOne,"Kilograms");
      strcpy(unitTwo,"Pounds");
      convert(name, unitOne, unitTwo, selectFunction);
    }
    /*Length*/
    else if(selectFunction == 3)
    {
      strcpy(name,"Length");
      strcpy(unitOne,"Centimeters");
      strcpy(unitTwo,"Inches");
      convert(name, unitOne, unitTwo, selectFunction);
    }
    /*Currency*/
    else if(selectFunction == 4)
    {
      strcpy(name,"Currency");
      strcpy(unitOne,"Euros");
      strcpy(unitTwo,"Dollars");
      convert(name, unitOne, unitTwo, selectFunction);
    }
    /*Volume*/
    else if(selectFunction == 5)
    {
      strcpy(name,"Volume");
      strcpy(unitOne,"Liters");
      strcpy(unitTwo,"Ounces");
      convert(name, unitOne, unitTwo, selectFunction);
    }
    else
    {
      printf("Invalid Option\n");
    }
    
    /*Ask the user if they would like to continue*/
    printf("Would you like to convert another value? (y/n)");
    scanf(" %c", &continueChar);
	printf("\n");
    if(continueChar == 'y')
    {
      printf("You entered y.\n\n");
      continue;
    }    
    else if(continueChar == 'n')
    {
	  printf("You entered n.\n");
      printf("Bye!\n");
      exit(1);
    }
    else
    {
      printf("Invalid option. Exiting.\n");
      exit(1);
    }
  }
  return 0;
}

/*Print results*/
void printTheResult(float convertFrom, char unitOne[20], 
float result, char unitTwo[20])
{
  printf("%.2f %s = %.2f %s\n", convertFrom, unitOne, result, unitTwo);
}

/*Convert*/
int convert(char name[20], char unitOne[20], 
char unitTwo[20], int selectFunction)
{
  int unitChoice;
  float convertFrom;
  float result;
  printf("You entered %s.\n", name);
  printf("Choose units:");
  scanf(" %d", &unitChoice);
  printf("\n");
  printf("1 - %s to %s\n", unitOne, unitTwo);
  printf("2 - %s to %s\n", unitTwo, unitOne);
  
  
  if(unitChoice == 1)
  {
    printf("You entered %s to %s.\n", unitOne, unitTwo);
    printf("Enter %s in %s", name, unitOne);
    scanf(" %f", &convertFrom);
	printf("\n");
    
    /*celsius to fahrenheit*/
    if (selectFunction == 1)
    {
      result = (convertFrom * 9/5)+32;
    }
    /*All other units must be positive*/  
    else if (convertFrom < 0)
    {
      printf("Error: Value should be a positive float.\n");
      return 0;
    }
    /*kilograms to pounds*/
    if (selectFunction == 2)
    {
      result = convertFrom * 2.20f;
    }
    /*centimeters to inches*/
    else if (selectFunction == 3)
    {
      result = convertFrom * 0.3937f;
    }
    /*euros to dollars*/
    else if (selectFunction == 4)
    {
      result = convertFrom / 0.9f;
    }
    /*liters to ounces*/
    else if (selectFunction == 5)
    {
      result = convertFrom * 33.814f;
    }
    printTheResult(convertFrom, unitOne, result, unitTwo);          
  }
  else if(unitChoice == 2)
  {
    printf("You entered %s to %s.\n", unitTwo, unitOne);
    printf("Enter %s in %s", name, unitTwo);
    scanf(" %f", &convertFrom);
	printf("\n");
    /*fahrenheit to celsius*/
    if (selectFunction == 1)
    {
      result = (convertFrom - 32) * 5/9;
    }
    /*All other units must be positive*/  
    else if (convertFrom < 0)
    {
      printf("Error: Value should be a positive float.\n");
      return 0;
    }
    /*pounds to kilograms*/
    if (selectFunction == 2)
    {
      result = convertFrom/2.2f;
    }
    /*inches to centimeters*/
    else if (selectFunction == 3)
    {
      result = convertFrom * 2.54f;  
    }
    /*dollars to euros*/
    else if (selectFunction == 4)
    {
      result = convertFrom * 0.90f;
    }
    /*ounces to liters*/
    else if (selectFunction == 5)
    {
      result = convertFrom / 33.814f;   
    }
    printTheResult(convertFrom, unitTwo, result, unitOne);
  }
  else
  {
	printf("Invalid Option\n");
  }
  return 0;
}