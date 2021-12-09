/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c eric.c
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "header.h"


/*void printMenu(int crimCount)*/
/*prints Menu & asks user to enter desired feature*/

/* THIS HAS NOW BEEN MOVED TO MAIN*/
/*{
    printf("\033[1;36m");
    printf("----------------------------------------------------------------\n");
    printf("> Welcome to the Criminal Database, what would you like to do? <\n");
    printf("----------------------------------------------------------------\n");
    printf("\033[0m");
    printf("1. Add criminal information\n"
           "2. Edit criminal profile\n"
           "3. Display all criminals (current count: %d/%d)\n"
           "4. Display specific criminals\n"
           "5. Save to database\n"
           "0. Exit program\n"
           "\n"
           "Enter the number matching your choice > ", crimCount, MAX_NUM_OF_CRIMINALS);
}*/


/*THIS HAS BEEN MOVED TO BACKEND*/
/*int skip(void)
{
    char skip = '*';
        while (skip == '*')
        {
          skip = getchar();
        }
    return 0;
}*/

/*THIS HAS BEEN MOVED TO EDITCRIM*/
/*void editCrim(criminal_t criminal[], int arrSize, int crimID)
{
    int i = crimID;
    int feature;
    int feature2;
    Prints criminal information that the user can edit
    printf("CRIMINAL INFORMATION:\n"
            "1. Name \n"
            "2. Sex \n"
            "3. Date of birth \n"
            "4. Residential Address \n"
            "5. Occupation \n"
            "6. Physical Characteristics  \n"
            "7. Current status \n"
            "8. Criminal/Offenses record \n"
            "Enter choice (number between 1-8)\n>");
      scanf("%d", &feature);
            
            adds user entry & checks if the user entry is valid
            switch (feature)
            {
                case 1:
                {
                  printf("Current name: %s %s\n", criminal[i].firstName, criminal[i].lastName);
                  printf("Enter new name as first name followed by second name: ");
                  scanf("%s %s", criminal[i].firstName, criminal[i].lastName);
                  break;
                }
                case 2:
                {
                  printf("Current sex [M/F]: %s\n", criminal[i].physique.sex);
                  printf("Enter new criminal ID: ");
                  scanf("%s", criminal[i].physique.sex);
                  break;
                }
                case 3:
                {
                  printf("Current date of birth: %d.%d.%d\n", criminal[i].dob.day, criminal[i].dob.month, criminal[i].dob.year);
                  printf("Enter new date of birth in format day month year: ");
                  scanf("%d.%d.%d", &criminal[i].dob.day, &criminal[i].dob.month, &criminal[i].dob.year);
                  break;
                }
                case 4:
                {
                  printf("Current Residential address: %d %s %s\n", criminal[i].resAddress.streetNumber, 
                  criminal[i].resAddress.streetName, criminal[i].resAddress.suburb);
                  printf("Enter new Residential address (street number, street name, suburb, state) separated by space: ");
                  scanf("%d %s %s %s", &criminal[i].resAddress.streetNumber, 
                  criminal[i].resAddress.streetName, criminal[i].resAddress.suburb, criminal[i].resAddress.state);
                  break;
                }
                case 5:
                {
                  printf("Current occupation: %s\n", criminal[i].occupation);
                  printf("Enter new occupation: ");
                  scanf("%s", criminal[i].occupation);
                  break;
                }
                case 6:
                {
                  printf("Current Physical Characteristics: %d %s\n", 
                  criminal[i].physique.height, criminal[i].physique.features);
                  printf("Enter new Physical Characteristics in order; height & features. \n Separated by space: ");
                  scanf("%d %s", 
                  &criminal[i].physique.height, criminal[i].physique.features);
                  break;
                }
                case 7:
                {
                 printf("Current status: %s\n", criminal[i].currentStatus);
                 printf("Enter new status: ");
                 scanf("%s", criminal[i].currentStatus);
                 break;
                }
                case 8:
                {
                  printf("CRIMINAL/OFFENSES RECORD:\n"
                         "1. Charge/reason for arrest.\n"
                         "2. Date of occurence\n"
                         "3. Address of offence\n"
                         "4. Name of officer who charged criminal\n"
                         "5. Brief description of offence\n"
                         "6. Officer statement\n"
                         "7. Victim statement\n"
                         "8. Witness statement\n"
                         "9. Individuals involved in crime\n"
                        "Enter choice (number between 1-9)\n>");
                  scanf("%d", &feature2);
                        adds user entry and checks of Offense record choice is valid
                        switch (feature2)
                        {
                            case 1:
                            {
                             printf("Current Charge: %s\n", criminal[i].crimHistory->charge);
                             printf("Enter new Charge (charge): ");
                             scanf("%s", criminal[i].crimHistory->charge);
                             break;
                            }
                            case 2:
                            {
                             printf("Current date of occurence: %d %d %d\n", criminal[i].crimHistory->occurrence.day, 
                             criminal[i].crimHistory->occurrence.month, criminal[i].crimHistory->occurrence.year);
                             printf("Enter new date of occurence (day, month, year as integers) separated by space: ");
                             scanf("%d %d %d", &criminal[i].crimHistory->occurrence.day, 
                             &criminal[i].crimHistory->occurrence.month, &criminal[i].crimHistory->occurrence.year);
                             break;
                            }
                            case 3:
                            {
                             printf("Current Address of offence: %s %s\n", 
                             criminal[i].crimHistory->crimLocation.streetName, 
                             criminal[i].crimHistory->crimLocation.suburb);
                             printf("Enter new Address of offence (street number, street name, suburb, state) separated by space: ");
                             scanf("%s %s", criminal[i].crimHistory->crimLocation.streetName, 
                             criminal[i].crimHistory->crimLocation.suburb);
                             break;
                            }
                            case 4:
                            {
                             printf("Current name of officer who charged criminal: %s\n", criminal[i].crimHistory->officer);
                             printf("Enter new name of officer who charged criminal: ");
                             scanf("%s", criminal[i].crimHistory->officer);
                             break;
                            }
                            case 5:
                            {
                             printf("Current description of offence: %s\n", criminal[i].crimHistory->descrip);
                             printf("Enter new description of offence: ");
                             scanf("%s", criminal[i].crimHistory->descrip);
                             break;
                            }
                            case 6:
                            {
                             printf("Current officer statement: %s\n", criminal[i].crimHistory->offStatement);
                             printf("Enter new officer statement: ");
                             scanf("%s", criminal[i].crimHistory->offStatement);
                             break;
                            }
                            case 7:
                            {
                             printf("Current victim statement: %s\n", criminal[i].crimHistory->victStatement);
                             printf("Enter new victim statement: ");
                             scanf("%s", criminal[i].crimHistory->victStatement);
                             break;
                            }
                            case 8:
                            {
                             printf("Current witness statement: %s\n", criminal[i].crimHistory->witnStatement);
                             printf("Enter new witness statement: ");
                             scanf("%s", criminal[i].crimHistory->witnStatement);
                             break;
                            } 
                            case 9:
                            {
                             printf("Current individuals involved: %s\n", criminal[i].crimHistory->whoInvolved);
                             printf("Enter new individuals involved: ");
                             scanf("%s", criminal[i].crimHistory->whoInvolved);
                             break;
                            }
                            default:
                            printf("Error. Please select a number between 1-9. Exiting...\n");
                        }
                 break;
                }
                default:
                printf("Error. Please select a number between 1-8. Exiting...\n");
            }

}*/

/*****************************************
 THIS HAS BEEN MOVED TO BACKEND
 *****************************************/
/*int dateIsValid(criminal_t criminal )
{
  if (criminal.dob.day < 0 && dob.day > 31){
    return 0;
  }
  if (date.month < 1 && date.month > 12){
    return 0;
  }
  if (date.year < 1 && date.year > 12){
    return 0;
  }
    return 1;
}*/

/*****************************************************
 * Checks the validity of user entry for the addresses
 *  
 * inputs:
 * 
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************//*UNFINISHED*/
/*int addressIsValid(criminal_t addr)
{
  if (criminal.resAddress.streetNumber < 0 && criminal.resAddress.streetNumber > 1000){
    return 0;
  }

  for (int i = 0; i < sizeof(criminal.resAddress.streetname) - 1; i += 1) {
    if ((criminal.resAddress.streetName[i] < 'A' && criminal.resAddress.streetName[i] > 'Z')
    || (criminal.resAddress.streetName[i] < 'a' && criminal.resAddress.streetName[i] > 'z')){
      return 0;
    }
  }

  for (int i = 0; i < sizeof(criminal.resAddress.suburb) - 1; i += 1) {
    if ((criminal.resAddress.suburb[i] < 'A' && criminal.resAddress.suburb[i] > 'Z')
    || (criminal.resAddress.suburb[i] < 'a' && criminal.resAddress.suburb[i] > 'z')){
      return 0;
    }
  }

  for (int i = 0; i < sizeof(criminal.resAddress.state) - 1; i += 1) {
    if ((criminal.resAddress.state[i] < 'A' && criminal.resAddress.state[i] > 'Z')
    || (criminal.resAddress.state[i] < 'a' && criminal.resAddress.state[i] > 'z')){
      return 0;
    }
  }

    return 1;
}
*/

 /*****************************************************
 * Checks the validity of user entry for the offense information
 *  
 * inputs:
 * 
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************/
/*
int offenseIsValid(offense_t off) 
{
  
}
*/

 /*****************************************************
 * Checks the validity of user entry for the physical characteristics 
 *  
 * inputs:
 * 
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************/
 

 /*****************************************************
 * Checks the validity of user entry for the basic criminal information
 *  
 * inputs:
 * 
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************/
