/********************************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Names and IDs:       13211608 Shaman Dutt          
                        13555887 Eric Kioko           
                        13897323 Olivia Farrugia      
                        13852987 Md Faisal Chaklader  
                        13534932 Yongqi Su            
 * Date of submission:  
 * Brief description of program: This program provides a functional database for the NSW police
 * to store criminal information that can be constantly updated and edited. The database also
 * provides compression and encryption functionalities for the database.
 **********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "H_MAIN.h"
#include "H_ADDCRIM.h"
#include "H_BACKEND.h"
#include "H_COMPRESSION.h"
#include "H_EDITCRIM.h"
#include "H_ENCRYPTION.h"
#include "H_IMAGES.h"
#include "H_SAVELOAD.h"
#include "H_SEARCHDISPLAY.h"

int main(void)
{
    /* define the criminals array */
    criminal_t criminals[MAX_NUM_OF_CRIMINALS];
    /* load in all the entries stored in the text file */
    COMPRESS(0);
    int crimCount =load_DB(criminals, MAX_NUM_OF_CRIMINALS);

    #ifdef DEBUG_LOADING
    printf("\033[0;33mDEBUG: In main - crimcount = %d\033[0m\n", crimCount);
    #endif

    if(crimCount==-1)
    {
        printf("Read error\n");
        exit(0);
    }

    while(1)
    {
        int choice;
        printMenu(crimCount);
        scanf(" %d", &choice);
        switch(choice)
        {
            /* feature 1 - add a criminal to the database */
            case 1:
            {
                /* call the add crim function */
                addCrim(criminals, crimCount);

                /* increment crim count */
                crimCount++; 

                /* save the database to the DB_STOAGE file */
                save_DB(criminals, MAX_NUM_OF_CRIMINALS, crimCount);
                escFunction();
                break;
            }

            /* feature 2 - edit a criminal that the user searched for */
            case 2:
            {
                printf("\n> Edit criminal profile <\n"
                "------------------------------------\n");

                /* define an array of matches */
                int matchedNames[crimCount];
                int matchArrSize=0;
                int choice;

                /* call searchName to index name results */
                matchArrSize = searchName(criminals, MAX_NUM_OF_CRIMINALS, matchedNames);

                /* display matches found */
                printCriminal(criminals, MAX_NUM_OF_CRIMINALS, matchedNames, matchArrSize);

                /* retrieve users desired match */
                printf("Enter the ID of the criminal you wish to edit\n> ");
                scanf("%02d", &choice);
                printf("You are editing criminal with ID:%2d\n", choice);

                /* edit specified criminal */
                editCrim(criminals, MAX_NUM_OF_CRIMINALS, choice);

                /* save the database to the DB_STOAGE file */
                save_DB(criminals, MAX_NUM_OF_CRIMINALS, crimCount);
                
                escFunction();
                break;
            }

            /* feature 3 - print all the criminals currently stored in the database */
            case 3:
            {
                /* print shortified list */
                printCrimlist(criminals, crimCount);

                /* print all data */
                print_DB(criminals, MAX_NUM_OF_CRIMINALS, crimCount);
                
                escFunction();     
                break;
            }

            /* feature 4 - print specifc matches of criminals the user searched for */
            case 4:
            {
                printf("\n> Display specific criminals <\n"
                "------------------------------------\n");
                /* define an array of matches */
                int matchedNames[crimCount];
                int matchArrSize=0;
                /* call searchName to index name results */
                matchArrSize = searchName(criminals, MAX_NUM_OF_CRIMINALS, matchedNames);
                /* pass the matchedNames array that has been edited in searchName to printfCrimnal */
                printCriminal(criminals, MAX_NUM_OF_CRIMINALS, matchedNames, matchArrSize);

                escFunction();
                break;
            }

            /* exit the program */
            case 0:
            {
                printf("Exiting program... cya dude!\n");
                save_DB(criminals, MAX_NUM_OF_CRIMINALS, crimCount);
                COMPRESS(1);
                return 0;
            }
            default:
            printf("ERROR: Invalid choice\n");
        }
    }
    return 0;
}
