/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c editcrim.c
*************************************************************************/

#include <stdio.h> /* printf, scanf */
#include <string.h> /* strcpy */
#include "H_MAIN.h" /**/
#include "H_EDITCRIM.h" /* editCrim */
#include "H_BACKEND.h" /* dateIsValid */

/* Author: Eric */
/****************************************************************************
 * Edits the information associated with a single criminal stored in the file 
 * inputs:
 * - array of criminals
 * - size of the array
 * - criminal ID.
 * outputs:
 * - none
 ****************************************************************************/
void editCrim(criminal_t criminal[], int arrSize, int crimID)
{
    int i = crimID;
    int choice;
    int choice2;
    int x; 

    /*Allows user to choose which criminal information to edit*/
    printf("\nCRIMINAL INFORMATION:\n"
           "1. Name \n"
           "2. Sex \n"
           "3. Date of birth \n"
           "4. Residential Address \n"
           "5. Occupation \n"
           "6. Height  \n"
           "7. Current status \n"
           "8. Criminal/Offenses record \n"
           "Enter choice (number between 1-8)\n>");
    scanf("%d", &choice);
          
    /*Adds user entry & checks if the user choice entry is valid*/
    switch (choice)
    {
        case 1:
        {
          /*Allows user to edit criminal name*/
          printf("\nCriminal name:\n");
          printf("Current name: %s %s\n", 
          criminal[i].firstName, criminal[i].lastName);
          printf("├─ Enter new first name: ");
          scanf(" %[^\n]", criminal[i].firstName);
          printf("└─ Enter new last name: ");
          scanf(" %[^\n]", criminal[i].lastName);
          break;
        }
        case 2:
        {
          /*Allows user to edit criminal sex*/
          printf("\nCriminal sex:\n");
          printf("Current sex [M/F]: %c\n", criminal[i].physique.sex);
          printf("└─ Enter new criminal sex [M/F]: ");
          scanf("%c ", &criminal[i].physique.sex);
          break;
        }
        case 3:
        {
          /*Allows user to edit criminal date of birth*/
          printf("\nCriminal D.O.B information:\n");
          printf("Current date of birth: %d.%d.%d\n", 
          criminal[i].dob.day, 
          criminal[i].dob.month, 
          criminal[i].dob.year);
          while (1)
          {
            /*Checks validity of day, month, year input*/
            printf("└─ Enter new date of birth in format day.month.year [1-31].[1-12].[0-2020]: ");
            scanf("%d.%d.%d[\n]\n", 
            &criminal[i].dob.day, 
            &criminal[i].dob.month, 
            &criminal[i].dob.year);

            x = dateIsValid(criminal[i].dob.day, 
            criminal[i].dob.month, 
            criminal[i].dob.year);
            if (x == 0)
            {
              printf("├─ ERROR: Date is invalid \n");
            }
            else
            {
              break;
            }
          }
          break;
        }
        case 4:
        {
          /*Allows user to edit residential address*/
          printf("\nResidential Address information:\n");
          printf("Current street number: %d \n", criminal[i].resAddress.streetNumber);
          printf("├─ Enter street number [integer only] > ");
          scanf("%d", &criminal[i].resAddress.streetNumber);

          printf("Current street name: %s \n", criminal[i].resAddress.streetName);
          printf("├─ Enter street name: "); 
          scanf(" %[^\n]", criminal[i].resAddress.streetName);

          printf("Current suburb: %s \n", criminal[i].resAddress.suburb);
          printf("├─ Enter new suburb: "); 
          scanf(" %[^\n]", criminal[i].resAddress.suburb);

          printf("Current state: %s \n", criminal[i].resAddress.state);
          printf("└─ Enter new state: "); 
          scanf(" %[^\n]", criminal[i].resAddress.state);
          break;
        }
        case 5:
        {
          /*Allows user to edit occupation*/
          printf("\nCurrent occupation: %s\n", criminal[i].occupation);
          printf("└─ Enter new occupation: ");
          scanf(" %[^\n]", criminal[i].occupation);
          break;
        }
        case 6:
        {
          /*Allows user to edit height*/
          printf("\nCurrent height: %lf\n", 
          criminal[i].physique.height);
          printf("└─ Enter new height: ");
          scanf(" %lf[^\n]", 
          &criminal[i].physique.height);
          break;
        }
        case 7:
        {
          /*Allows user to choose new criminal status*/
          int status;
          while(1)
          {
            printf("\nCurrent status: %s\n", criminal[i].currentStatus);
            printf("Enter new status between [1-3]: ");
            printf("\n1. Fugitive\n2. Incarcerated\n3. Released\n");
            printf("> ");
            scanf(" %d[^\n]", &status);
            if (status == 1)
            {
              char inputStatus[] = "Fugitive";
              strcpy(criminal[i].currentStatus, inputStatus);
              break;
            } else if (status == 2)
            {
              char inputStatus[] = "Incarcerated";
              strcpy(criminal[i].currentStatus, inputStatus);
              break;
            } else if (status == 3)
            {
              char inputStatus[] = "Released";
              strcpy(criminal[i].currentStatus, inputStatus);
              break;
            } else
            {
              printf("Invalid input.\n");
              continue;
            }
          }
          break;
        }
        case 8:
        {
          /*Allows user to choose offence record information to edit*/
          printf("\nCRIMINAL/OFFENCES RECORD:\n"
                  "1. Date of offense\n"
                  "2. Location of offence\n"
                  "3. Brief description of offence\n"
                "Enter choice (number between 1-3)\n>");
          scanf("%d", &choice2);
                /*adds user entry and checks if Offence record choice is valid*/
                switch (choice2)
                {
                    case 1:
                    {
                      /*Allows user to edit date of offence*/
                      printf("\nCurrent date of occurrence: %d %d %d\n", criminal[i].crimHistory->occurrence.day, 
                      criminal[i].crimHistory->occurrence.month, criminal[i].crimHistory->occurrence.year);
                      printf("Enter new date of occurrence (day, month, year as integers) separated by space: ");
                      scanf("%d %d %d", &criminal[i].crimHistory->occurrence.day, 
                      &criminal[i].crimHistory->occurrence.month, &criminal[i].crimHistory->occurrence.year);
                      break;
                    }
                    case 2:
                    {
                      /*Allows user to edit address of offence*/
                      printf("\nCurrent Address of offence: %s %s\n", 
                      criminal[i].crimHistory->crimLocation.streetName, 
                      criminal[i].crimHistory->crimLocation.suburb);
                      printf("Enter new street name: ");
                      scanf(" %[^\n]", criminal[i].crimHistory->crimLocation.streetName);
                      printf("Enter new suburb: ");
                      scanf(" %[^\n]", criminal[i].crimHistory->crimLocation.suburb);
                      break;
                    }
                    case 3:
                    {
                      /*Allows user to edit brief description of offence*/
                      printf("Current brief description of offence: %s\n", criminal[i].crimHistory->descrip);
                      printf("Enter new brief description of offence: ");
                      scanf(" %[^\n]", criminal[i].crimHistory->descrip);
                      break;
                    }
                    /*Prints error message when invalid offence record choice is inputted*/
                    default:
                    printf("Error. Please select a number between 1-3. Exiting...\n");
                }
          break;
        }
        /*Prints error message when invalid criminal information choice is inputted*/
        default:
        printf("Error. Please select a number between 1-8. Exiting...\n");
    }

}
