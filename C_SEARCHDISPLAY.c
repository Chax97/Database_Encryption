/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c searchdisplay.c

Include everything relating to searching and displaying from database.
*************************************************************************/

#include <stdio.h> /* printf, scanf */
#include <stdlib.h> 
#include <string.h> /* strlen, strcmp */
#include <math.h>
#include "H_MAIN.h"
#include "H_SEARCHDISPLAY.h"

/* Author: shaman */
/*************************************************************************
 * This function displays all crimals currently stored in the database.
 * inputs:
 * - none
 * outputs:
 * - none
 *************************************************************************/
void printCrimlist(criminal_t criminals[], int crimCount)
{
    if(crimCount<=0)
    {
        printf("\nERROR: Database empty. Nothing to display.\n");
        return;
    }
    int count=0;
    printf("The following table includes the ID / SURNAME / FIRST NAME / STATUS of every criminal\nentry. A full list of all the data is printed in A_DB_DISPLAY.txt\n");
    printf("\n\033[1;36m           <<< DISPLAYING LIST OF ALL CRIMINALS FROM DATABASE >>>          \033[0m\n");
    printf("+------+------------------------+------------------------+--------------------+\n");
    printf("|  ID  |        SURNAME         |       FIRST NAME       |       STATUS       |\n");
    printf("+------+------------------------+------------------------+--------------------+\n");
    while(count<crimCount)
    {
        /* print ID */
        printf("|  %d", count);
        if(count<10){
            printf("   ");
        }
        if(count>=10 && count<100){
            printf("  ");
        }

        /* print surname */
        printf("| %s", criminals[count].lastName);
        int SNlen = strlen(criminals[count].lastName);
        int j;
        for(j=0; j<(MAX_NAME_LEN - SNlen -1); j++)
        {
            printf(" ");
        }

        /* print first name */
        printf("| %s", criminals[count].firstName);
        int FNlen = strlen(criminals[count].firstName);
        int k;
        for(k=0; k<(MAX_NAME_LEN - FNlen -1); k++)
        {
            printf(" ");
        }

        printf("| %s", criminals[count].currentStatus);
        int STlen = strlen(criminals[count].currentStatus);
        int l;
        for(l=0; l<(MAX_STATUS_LEN - STlen -1); l++)
        {
            printf(" ");
        }
        printf("|\n");
        count++;
    }
    printf("+------+------------------------+------------------------+--------------------+\n");
}

/* faisal */
/*****************************************
 * This function prompts the user to input a name and checks the database for any matches
 * of the name. If there are no matches returns 0, if there are matches, return 1 and store
 * the matching indexes in an array called matches
 * inputs: 
 * - 
 ****************************************/
 
int searchName(criminal_t criminals [], int crimCount, int matchedNames[])
{

    int sel=0;
    
    
    printf("What do you want to search by, enter 1 or 2\n");
    printf("1. First name\n");
    printf("2. Last name\n");

    while(0==0)
    {
        scanf("%d", &sel);

        #ifdef DEBUG
        printf("DEBUG: user inputed %d\n", sel);
        #endif

        if(sel > 0 && sel < 3)
        {
            break;
        }
        else
        {
            printf("Invalid input, enter again>\n");
            continue;
        }
    }

    
    int A = 'A';
    int z = 'z';
    int i;
    int nameLen;
    int invalidCount=0;
    char nameToSearch[MAX_NAME_LEN];
    do
    {
        if(invalidCount>0){
            printf("Invalid Input\n");
        }
        invalidCount = 0;
        if(sel == 1)
        {
            printf("Enter first name> ");
        }
        else if(sel == 2)
        {
            printf("Enter last name> ");
        }

        scanf("%s", nameToSearch);
        nameLen = strlen(nameToSearch);
        for(i=0;i<nameLen;i++)
        {
            /* checks between A - z */
            if( (nameToSearch[i]) - A < 0 || (nameToSearch[i]) - z >0)
            {
                /* if there is an invalid char */
                invalidCount++;
            }    
        }
    }while(invalidCount>0);


    int k=0;
    
    for(i =0;i<crimCount;i++)
    {        
            
        if(sel == 1)
        {       
            if(strcmp(nameToSearch,criminals[i].firstName)==0)
            {
                matchedNames[k] = i;
                #ifdef DEBUG
                printf("DEBUG: matched firstname of criminals[%d] to matchedNames[%d]\n", i, k);
                #endif
                k++;
            }
        }    
     
        else
        {
            if(strcmp(nameToSearch,criminals[i].lastName) == 0)
            {
                matchedNames[k] = i;
                k++;
            }
        }    
    }

    #ifdef DEBUG
    printf("DEBUG: matchedNames array:\n");
    int a;
    for(a=0; a<k; a++)
    {
        printf("matchedNames[%d] = %d\n", a, matchedNames[a]);
    }
    #endif
    return k;
}

/*****************************************
 * This function takes the matches[] array which any of the search functions edits and it 
 * prints all the data of the ID's stored within the matches[] array
 * inputs:
 * - int matches[] (the array)
 * - int size_of_matches (size of the array)
 * outputs:
 * - none
 *****************************************/
void printCriminal(criminal_t criminals[], int crimArrSize, int matchedNames[], int matchArrSize)
{
   int i=0,j;
   if(matchArrSize == 0)
   {
       printf("\nNo matches.\n");
       return;
   }
   else if(matchArrSize > 0)
   {
        printf("\n\033[1;36m---DISPLAYING MATCHING CRIMINALS FROM DATABASE---\n\033[0m");
       for (j = 0; j < matchArrSize; j++)
       {
            i = matchedNames[j];
            printf("ID: %02d - NAME: %s %s\n", i, criminals[i].firstName, criminals[i].lastName);
             
       }
    }
}

/* ???? */
void printMatchedIDs(int matchArray[], int matchArrSz)
{
    int i;
    printf("Matches found with following ID: ");
    for(i=0; i<matchArrSz; i++)
    {
        printf("%02d ", matchArray[i]);
    }
    printf("\n");
}
