/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c backend.c


This file includes all backend miscellaneous functions such as 
verification and skip functions.
*************************************************************************/
#include <stdio.h> /* printf, scanf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */
/*#include <math.h>*/
#include "H_MAIN.h" /**/
#include "H_BACKEND.h" /*printMenu, dateIsValid, skip*/

/* Author: Eric */
/*****************************************************************
 * Prints the menu to allow user to enter desired feature 
 * inputs:
 * -crimCount
 * outputs:
 * - N/A
******************************************************************/
void printMenu(crimCount)
{
  printf("\033[1;36m");
  /*printf("----------------------------------------------------------------\n");*/
  printf("> Welcome to the Criminal Database!!! <\n");
  printf("\033[0m");
  printf("__________________________________________________________________\n");
  printf("1. Add a criminal to the database\n");
  printf("2. Edit criminal profile\n");
  printf("3. Display all criminals (current count: %d/%d)\n", crimCount, MAX_NUM_OF_CRIMINALS);
  printf("4. Display specific criminals (NEEDS UPDATING)\n");
  printf("0. Exit program\n");
  printf("__________________________________________________________________\n");
  printf("What would you like to do? Please enter a number > ");
}

/* Author: Eric */
/********************************************************
 * Checks the validity of user entry for the criminal dates
 * inputs:
 * - day
 * - month
 * - year
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************/
int dateIsValid(int day, int month, int year)
{
  int status = 1;
  /*Checks whether the date is valid*/
  if (day < 1 || day > 31)
  {
    status = 0;
  }
  if (month < 1 || month > 12)
  {
    status = 0;
  }
  if (year < 0 || year > 2020)
  {
    status = 0;
  }
  return status;
}




/* Author: Eric */
/*****************************************************************
 * Allows the user to skip any unnecessary information when adding 
 * criminal information 
 * 
 * inputs:
 * - none
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************************/
int skip(void)
{
  /* skips a section/non mandatory information when adding criminal information*/
  char skip;
  printf("[Enter '*' to skip this field]\n");
  scanf("%c", &skip);
  if (skip == '*')
  {
    return 1;
    }
  else 
  {
    return 0;
  }
}

/* shaman */
/***************************************************************************
 * this function ask the user to enter a 0 to successfully exit the feature. 
 * (The purpose of this function is to stop printing the menu again after a
 * feature has finished, so as to make the program look a little neater).
 * inputs:
 * - none
 * outputs:
 * - none (int only for the function to finish and return 0) 
 ****************************************************************************/
int escFunction (void)
{
    printf("\nEnter 0 to return to menu...");
    char enter = 0; 

    while (enter != '0') 
    {
        enter = getchar();   
    }
    return 0;
}


/* shaman */
/*************************************************************************
 * This function repeatedly asks the user to input 0 or 1, until a correct
 * value is inputed. It then returns which value the user inputed. This
 * function is used for the escape sequence at the end of a feature.
 * inputs:
 * - void
 * outputs:
 * - int (returns 0 or 1)
 *************************************************************************/
int ExCont(void)
{
    int ExCont;
    while(1)
    {
        /*printf("Enter 0 to exit or 1 to repeat the feature\n");*/
        scanf("%d", &ExCont);

        if(ExCont == 1)
        {
            break;
        }
        if(ExCont == 0)
        {
            break;
        }
        else if(ExCont<0 || ExCont>1)
        {
            printf("Invalid input\n");
            continue;
        }
    }
    return ExCont;
}

/*
int intOrChar(float input)
{
    int status;
    int test;
    test=(int)input;
    ++test;
    if((test-input)!=1)
    {
        status=1;
    }
    else
    {
        status=0;
    }
    return status;
}
*/

/* Author:Shaman */
/****************************************************
*
*
*
*****************************************************/
void printCharLine(FILE* fp, char ch, int len)
{
  int i;
  for(i=0; i<len; i++)
  {
    fprintf(fp, "%c", ch);
  }
}




/* Author: Eric */
/*****************************************************
 * Checks the validity of user entry for the addresses
 *  
 * inputs:
 * 
 * outputs:
 * - return;
 *          1 - if input is valid      
 *          0 - invalid input
 *****************************************************/
/*int addressIsValid(int streetNumber, char streetName[MAX_STREET_LEN], char suburb[MAX_SUBURB_LEN], char state[MAX_STATE_LEN])
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
}*/
