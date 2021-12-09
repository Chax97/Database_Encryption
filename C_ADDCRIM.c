/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c addcrim.c

NEED TO FIX FUNCTION DESCRIPTIONS

https://www.includehelp.com/c/c-program-to-read-string-with-spaces-using-scanf-function.aspx

*************************************************************************/
#include <stdio.h> /*printf, scanf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strcpy*/
/*#include <math.h> */

#include "H_MAIN.h"
#include "H_BACKEND.h"
#include "H_ADDCRIM.h"
#include "H_IMAGES.h"

/* Contributors: eric, bo, faisal, shaman */
/****************************************************************************
 * Allows user to add the information associated with a single criminal 
 * stored in the file 
 * inputs:
 * - array of criminals
 * - size of the array
 * - criminal ID.
 * outputs:
 * - none
 ****************************************************************************/
void addCrim(criminal_t criminals[], int crimCount)
{
    char temp; /* for input buffer */
    /* To stop function when maximum number of criminals has been fixed */
    if(crimCount>MAX_NUM_OF_CRIMINALS)
    {
        printf("Database memory full.\nExiting...\n");
        return;
    }
    char fn[MAX_NAME_LEN];
    char ln[MAX_NAME_LEN];

    printf("\n<<< ADD CRIMINAL TO DATABASE >>>\n");
    printf("You are now entering a criminal into the database," 
    "please enter the\nrequested information in the following fields." 
    "The input arguments\nare presented in [square brackets]:\n");
    printf("NOTE: Please adhere to the input arguments, other types of inputs"
    "\neg a character into an 'integer only' input may crash the program.\n");

    /*Allows user to add name*/
    printf("\nCriminal name and sex:\n");
    printf("├─ Enter first name [max %d characters] > ", 
    MAX_NAME_LEN);
    printf("\033[1;31m");
    scanf(" %[^\n]", fn);
    printf("\033[0m");
    strcpy(criminals[crimCount].firstName, fn);
    printf("├─ Enter last name [max %d characters] > ", 
    MAX_NAME_LEN);
    printf("\033[1;31m");
    scanf(" %[^\n]", ln);
    printf("\033[0m");
    strcpy(criminals[crimCount].lastName, ln);

    /* Allows user to add sex & checks for invalid input */
    while(1)
    {
        char ch;
        printf("└─ Enter sex [M/F] > ");
        scanf(" %c[^\n]", &ch);
        if(ch=='M' || ch=='F')
        {
            criminals[crimCount].physique.sex = ch;
            break;
        }
        else
        {
            /* Prints error message when user has inputted anything else other than M/F */
            printf("├─ ERROR: Invalid input...\n");
            continue;
        }
        printf("\n");
    }

    while(1)
    {
        /* Allows user to add date of birth */
        printf("\nCriminal D.O.B information:\n");
        printf("├─ Enter numerical day of birth [1-31] > ");
        scanf(" %d[^\n]", &criminals[crimCount].dob.day);
        printf("├─ Enter numerical month of birth [1-12]  > ");
        scanf(" %d[^\n]", &criminals[crimCount].dob.month);
        printf("└─ Enter year of birth [0-2020] > ");
        scanf(" %d[^\n]", &criminals[crimCount].dob.year);
    
        /* Checks validity of the date of birth */
        int dob = dateIsValid(criminals[crimCount].dob.day, 
        criminals[crimCount].dob.month, 
        criminals[crimCount].dob.year);
        if (dob == 0) 
        {
            printf("   ERROR: Date is invalid \n");
            continue;
        }
        else
        {
            break;
        }
    }  

    /* char temp;  buffer for scanning string */
    printf("\nCriminal physique details:\n");

    printf("└─ Enter height (in cm) [integer only] > ");
    scanf(" %lf[\n]\n", &criminals[crimCount].physique.height);
    scanf("%c",&temp); /* buffer the input */

    /* Allows user to add residential address */
    printf("\nEnter Residential Address information:\n");

    printf("├─ Enter street number [integer only] > ");
    scanf(" %d[^\n]", &criminals[crimCount].resAddress.streetNumber);
    scanf("%c",&temp); /* buffer the input */

    printf("├─ Enter street name [max %d characters] > ", MAX_STREET_LEN);
    scanf(" %[^\n]", criminals[crimCount].resAddress.streetName);
    scanf("%c",&temp); /* buffer the input */

    printf("├─ Enter suburb [max %d characters] > ", MAX_SUBURB_LEN);
    scanf(" %[^\n]", criminals[crimCount].resAddress.suburb); 
    scanf("%c",&temp); /* buffer the input */

    printf("└─ Enter state [max %d characters] > ", MAX_STATE_LEN);
    scanf(" %[^\n]", criminals[crimCount].resAddress.state);
    scanf("%c",&temp); /* buffer the input */

    /* Allows user to select criminal status */
    printf("\nSelect criminal status of %s %s [1-3]:\n", 
    criminals[crimCount].firstName, criminals[crimCount].lastName);

    while(1)
    {
        printf("1. Fugitive\n2. Incarcerated\n3. Released\n");
        printf("> ");
        int status;
        scanf(" %d[^\n]", &status);
        if(status==1)
        {
            char inputStatus[] = "Fugitive";
            strcpy(criminals[crimCount].currentStatus, inputStatus);
            printf("Criminal has been registered as a fugitive\n");
            break;
        }
        if(status==2)
        {
            char inputStatus[] = "Incarcerated";
            strcpy(criminals[crimCount].currentStatus, inputStatus);
            printf("Criminal has been registered as incarcerated\n");
            break;
        }
        if(status==3)
        {
            char inputStatus[] = "Released";
            strcpy(criminals[crimCount].currentStatus, inputStatus);
            printf("Criminal has been registered as released\n");
            break;
        }
        else
        {
            printf("\nInvalid input, please select from 1-3\n");
            continue;
        }
    }
    scanf("%c",&temp); /* buffer the input */
    
    /* Allows user to add occupation */
    printf("\nEnter occupation [max %d characters] > ", MAX_OCCUP_LEN);
    scanf(" %[^\n]", criminals[crimCount].occupation);
    scanf("%c",&temp); /* buffer the input */

    int chargeNo = 0;
    criminals[crimCount].numCharges = 0;
    /* Allows user to enter criminal history information */
    while (chargeNo < MAX_OFFENSES_COMMITTED)
    {
        char yn;
        printf("\nCriminal #%02d %s %s has %d offences " 
        "in their criminal history.\n", crimCount, fn, ln, chargeNo);
        printf("Would you like to add an offence? " 
        "(max no. offences possible = %d)\n[Y/N] > ", MAX_OFFENSES_COMMITTED);
        scanf(" %c", &yn);

        if(yn == 'N')
        {
            printf("Criminal has been registered with %d offences under their name.\n", 
            chargeNo);
            break;
        }
        else if(yn == 'Y')
        {
            /* Allows user to add offence information */
            printf("\nEnter offence information:\n");
            while(1)
            {
                printf("Enter date of offence:\n");
                printf("├─ Enter numerical day of occurence [1-31] > ");
                scanf(" %d[\n]\n", &criminals[crimCount].crimHistory[chargeNo].occurrence.day);
                printf("├─ Enter numerical month of occurence [1-12]  > ");
                scanf(" %d[\n]\n", &criminals[crimCount].crimHistory[chargeNo].occurrence.month);
                printf("└─ Enter year of occurence [0-2020] > ");
                scanf(" %d[\n]\n", &criminals[crimCount].crimHistory[chargeNo].occurrence.year);

                /* Checks validity of the date of offence */
                int doc = dateIsValid(criminals[crimCount].crimHistory[chargeNo].occurrence.day,
                criminals[crimCount].crimHistory[chargeNo].occurrence.month,
                criminals[crimCount].crimHistory[chargeNo].occurrence.year);
                if (doc == 0) 
                {
                    printf("   ERROR: Date is invalid \n");
                    continue;
                }
                else
                {
                    break;
                }
            }   

            /* Allows user to add location of offence */
            printf("\nEnter location of offence:\n");
            printf("├─ Enter streetName [max %d characters] > ", MAX_STREET_LEN);
            scanf(" %[^\n]", 
            criminals[crimCount].crimHistory[chargeNo].crimLocation.streetName);
            scanf("%c",&temp); /* buffer the input */

            printf("└─ Enter suburb [max %d characters] > ", MAX_STATE_LEN);
            scanf(" %[^\n]",
            criminals[crimCount].crimHistory[chargeNo].crimLocation.suburb);
            scanf("%c",&temp); /* buffer the input */

            #ifdef DEBUG_LOADING
            printf("\033[0;33mDEBUG: scanning i = %d into crimID = %d\033[0m\n"
            , i, crim_being_loaded);
            #endif 
            
            /* Allows user to add brief decription of offence */
            printf("\nEnter brief description of offence [max %d characters]>", 
            MAX_DESCRIP_LEN);
            scanf(" %[^\n]", 
            criminals[crimCount].crimHistory[chargeNo].descrip);
            scanf("%c",&temp); /* buffer the input */

            #ifdef DEBUG_ADDCRIM
            printf("\033[0;33m");
            printf("DEBUG: saved string: \n%s\n", 
            criminals[crimCount].crimHistory[chargeNo].descrip);
            printf("\033[0m");
            #endif

            chargeNo++;
            criminals[crimCount].numCharges++;
        }
        else
        {
            printf("Invalid input.\n");
            continue;
        }
    }

    #ifdef DEBUG_ADDCRIM
    printf("\033[0;33m");
    printf("DEBUG: Stored criminal with %d offences\n", 
    criminals[crimCount].numCharges);
    printf("\033[0m");
    #endif
    
    /* ask user for image */
    char img = 0;
    printf("\nIMAGE UPLOAD:\n");
    printf("Would you like to upload an image of %s %s? [Y/N] >", 
    criminals[crimCount].firstName, criminals[crimCount].lastName);
    scanf(" %c[^\n]", &img);
    printf("Processing... This will take a few seconds...\n");
    if(img=='Y')
    {
        image_to_bin(crimCount);
        bin_to_image(crimCount);
        printf("Image uploaded successfully, with filename: "
        "\033[0;33mencrypt%d\033[0m\n", crimCount);
    }
    else
    {
        printf("No image uploaded.\n");
    }

    printf("\n");
    /* Prints information storage confirmation message */
    printf("\033[1;30m<<< CRIMINAL INFORMATION STORED >>>\033[0m\n"
    "\033[0;33mInformation for criminal: "
    "\033[1;31mID# %02d\033[0m \033[1;31m%s %s\033[0m "
    "\033[0;33mhas been added to the database.\033[0m\n",crimCount, fn, ln);
}
