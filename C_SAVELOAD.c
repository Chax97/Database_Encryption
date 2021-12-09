/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c C_SAVELOAD.c
*************************************************************************/
#include <stdio.h> /* printf, scanf */
#include <string.h>
#include "H_MAIN.h"
#include "H_SAVELOAD.h"
#include "H_IMAGES.h"
#include "H_BACKEND.h"

/* shaman */
/*****************************************
 * this function saves all current criminal entries from the criminals[] array
 * to a database A_DB_STORAGE, in the order they were entered into the array.
 * This database prints the array information in a neat manner for USER READING.
 * inputs:
 * - const criminals[] (criminals array, const because no change)
 * - int arrSize (passing the array size)
 * - int entries (no of criminals entered so far)
 * outputs:
 * - none 
 *****************************************/
 void print_DB (const criminal_t criminals[], int arrSize, int crimCount)
 {
    /* open the file */
    FILE* fp = NULL; /* file stream */
    fp = fopen(DB_READ, "w"); /* opening the text file for writing */
    if (fp == NULL) /* if file open was not successful */
    {
        printf("file error\n");
        return;
    }
    printCharLine(fp, '=', (PRINT_LINE_LEN-58)/2);
    fprintf(fp, "<<< EXTENDED INFORMATION FOR ALL CRIMINALS IN DATABASE >>>");
    printCharLine(fp, '=', (PRINT_LINE_LEN-58)/2);
    fprintf(fp, "\n");

    /* process of fprinting all the saved data into the new textfile */
    int i=0;
    while(i<crimCount)
    {
        printCharLine(fp, '_', PRINT_LINE_LEN);
        fprintf(fp, "\n");

        /* print in the crimCount/index/ID */
        fprintf(fp, "|                     ID: %02d", i);
        printCharLine(fp, ' ', PRINT_LINE_LEN-29);
        fprintf(fp, "|\n");
        fprintf(fp, "|                   NAME: %s %s", criminals[i].firstName, criminals[i].lastName);
        printCharLine(fp, ' ', PRINT_LINE_LEN-28-strlen(criminals[i].firstName)-strlen(criminals[i].lastName));
        fprintf(fp, "|\n");
        fprintf(fp, "|                 GENDER: %c", criminals[i].physique.sex);
        printCharLine(fp, ' ', PRINT_LINE_LEN-28);
        fprintf(fp, "|\n");
        fprintf(fp, "|          DATE OF BIRTH: %02d/%02d/%04d", criminals[i].dob.day, criminals[i].dob.month, criminals[i].dob.year);
        printCharLine(fp, ' ', PRINT_LINE_LEN-37);
        fprintf(fp, "|\n");
        int height = criminals[i].physique.height;
        fprintf(fp, "|                 HEIGHT: %d cm", height);
        if(height<10)
        {
            printCharLine(fp, ' ', PRINT_LINE_LEN-31);
            fprintf(fp, "|\n");
        }
        if(height>=10 && height<100)
        {
            printCharLine(fp, ' ', PRINT_LINE_LEN-32);
            fprintf(fp, "|\n");
        }
        if(height>=100)
        {
            printCharLine(fp, ' ', PRINT_LINE_LEN-33);
            fprintf(fp, "|\n");
        }
        int sno = criminals[i].resAddress.streetNumber;
        char sna[MAX_STREET_LEN];
        char sub[MAX_SUBURB_LEN];
        char sta[MAX_STATE_LEN];
        strcpy(sna, criminals[i].resAddress.streetName);
        strcpy(sub, criminals[i].resAddress.suburb);
        strcpy(sta, criminals[i].resAddress.state);
        fprintf(fp, "|    RESIDENTIAL ADDRESS: %d %s St %s %s", sno, sna, sub, sta);
        char snoLen[10];
        sprintf(snoLen, "%d", sno);
        int resprintlen = PRINT_LINE_LEN-33-strlen(snoLen)-strlen(sna)-strlen(sub)-strlen(sta);
        printCharLine(fp, ' ', resprintlen);
        fprintf(fp, "|\n");
        fprintf(fp, "|             OCCUPATION: %s", criminals[i].occupation);
        printCharLine(fp, ' ', PRINT_LINE_LEN-27-strlen(criminals[i].occupation));
        fprintf(fp, "|\n");
        fprintf(fp, "|CURRENT CRIMINAL STATUS: %s", criminals[i].currentStatus);
        printCharLine(fp, ' ', PRINT_LINE_LEN-27-strlen(criminals[i].currentStatus));
        fprintf(fp, "|\n");
        printCharLine(fp, '/', PRINT_LINE_LEN);

        /* print criminal history */
        fprintf(fp, "\nCRIMINAL HISTORY:\n");
        if(criminals[i].numCharges == 0)
        {
            fprintf(fp, "No charges found.\n");
        }
        else
        {
            int count=0;
            while(count<criminals[i].numCharges)
            {
                /* print offence number */
                fprintf(fp, "\nOFFENCE #%d:\n", count);

                /* print date of offence */
                fprintf(fp, "DATE OF OFFENSE: %d/%d/%d\n", 
                criminals[i].crimHistory[count].occurrence.day,
                criminals[i].crimHistory[count].occurrence.month,
                criminals[i].crimHistory[count].occurrence.year
                );

                /* print location of offense */
                fprintf(fp, "LOCATION OF OFFENSE: %s, %s\n", 
                criminals[i].crimHistory[count].crimLocation.streetName, 
                criminals[i].crimHistory[count].crimLocation.suburb);

                /* print descrip */
                fprintf(fp, "DESCRIPTION OF OFFENSE:\n%s\n", criminals[i].crimHistory[count].descrip);

                /* go to the next offence */
                count++;
            }
        }

        /* final ////// line */
        printCharLine(fp, '/', PRINT_LINE_LEN);
        fprintf(fp, "\n\n");

        i++;
    }
    fclose(fp); /* close the file after done with it */
}

/* shaman */
/*****************************************
 * This function saves all current criminal entries from criminals[] array
 * to a database DB_LOAD, in the order they were entered into the array. 
 * This database will be used FOR THE PROGRAM TO LOAD FROM.
 * inputs:
 * - const criminals[] (criminals array, const because no change)
 * - int arrSize (passing the array size)
 * - int entries (no of criminals entered so far)
 * outputs:
 * - none 
 *****************************************/
void save_DB (const criminal_t criminals[], int arrSize, int crimCount)
 {
    /* open the file */
    FILE* fp = NULL; /* file stream */
    fp = fopen(DB_LOAD, "w"); /* opening the text file for writing */
    if (fp == NULL) /* if file open was not successful */
    {
        printf("file error\n");
        return;
    }

    /* process of fprinting all the saved data into the new textfile */
    int i=0;
    while(i<crimCount)
    {
        /* print in the crimCount/index/ID */
        fprintf(fp, "%d\n", i);

        /* print in criminal name */
        fprintf(fp, "--%s | %s | %c\n", criminals[i].firstName, criminals[i].lastName, criminals[i].physique.sex);

        /* print in date of birth */
        fprintf(fp, "--DOB: %d/%d/%d :END_DOB\n", criminals[i].dob.day, criminals[i].dob.month, criminals[i].dob.year);

        /* print in height */
        fprintf(fp, "--HEIGHT: %lf :END_HEIGHT\n", criminals[i].physique.height);

        /* print in residential address */
        fprintf(fp, "--RESADD_STREETNO: %d :END_RESADD_STREETNO\n", criminals[i].resAddress.streetNumber);
        fprintf(fp, "--RESADD_STREETNAME: %s :END_RESADD_STREETNAME\n", criminals[i].resAddress.streetName);
        fprintf(fp, "--RESADD_SUBURB: %s :END_RESADD_SUBURB\n", criminals[i].resAddress.suburb);
        fprintf(fp, "--RESADD_STATE: %s :END_RESADD_STATE\n", criminals[i].resAddress.state);

        /* print in criminal status */
        fprintf(fp, "--STATUS: %s :END_STATUS\n", criminals[i].currentStatus);

        /* print in occupation */
        fprintf(fp, "--OCCUP: %s :END_OCCUP\n", criminals[i].occupation);

        /* print in num of charges */
        fprintf(fp, "--NUMCHARGES: %d :END_NUMCHARGES\n", criminals[i].numCharges);

        /* print in all offences */
        int count = 0;
        while(count<criminals[i].numCharges)
        {
            /* print number of offence */
            fprintf(fp, "--OFFNUM: %d :END_OFFNUM\n", count);

            /* print in offence date */
            fprintf(fp, "----OFFDATE: %d/%d/%d :END_OFFDATE\n", 
            criminals[i].crimHistory[count].occurrence.day, 
            criminals[i].crimHistory[count].occurrence.month, 
            criminals[i].crimHistory[count].occurrence.year);

            /* print in location of offense */
            fprintf(fp, "----OFFLOC_STREETNAME: %s :END_OFFLOC_STREETNAME\n", 
            criminals[i].crimHistory[count].crimLocation.streetName);
            fprintf(fp, "----OFFLOC_SUBURB: %s :END_OFFLOC_SUBURB\n", 
            criminals[i].crimHistory[count].crimLocation.suburb);

            /* print in description of offense */
            fprintf(fp, "----DESCRIP: %s :END_DESCRIP\n", 
            criminals[i].crimHistory[count].descrip);

            count++;
        }
        i++;
    }
    fclose(fp); /* close the file after done with it */
 }

/*******/

void endBuff(char buffer[], char outputS[])
{
    int a=0;
    while(a< strlen(buffer)-1 )
    {
        if(buffer[a]==':' && buffer[a+1]=='E')
        {
            buffer[a-1]='\0';
            break;
        }
        a++;
    }
    strcpy(outputS, buffer);
    buffer[0]='\0';
}

/* Author: Shaman */
/* this function loads the data stored within the database text file into the program,
 * and returns the number of entries loaded i.e. the crimCount left off from the last
 * time the program saved entries
 */
int load_DB(criminal_t criminals[], int arrSize)
{
    FILE* fp = NULL; /* file stream */
    fp = fopen(DB_LOAD, "r"); /* opening the text file for reading */
    if (fp == NULL) /* if file open was not successful */
    {
        /* if file opening error, return -1 and exit the function */
        printf("ERROR: No database storage file (DB_STORAGE) found.\n");
        return 0;
    }

    int crim_being_loaded=0;
    int loaded=0;
    /* check filesize, if = 1 -> there are no entries stored */
    fseek(fp,0,SEEK_END);
    int fs = ftell(fp);
    if(fs <= 1)
    {
        #ifdef DEBUG_LOADING
        printf("\033[0;33mDEBUG: filesize = %d - returning crim_being_loaded = %d\n\033[0m", fs, loaded);
        #endif

        return loaded;
    }
    rewind(fp);

    int i=0;
    while(i<arrSize)
    {
        /* scan the first integer, which will be the criminal index/ID.
        If no index is found, that means there are no (more) criminals inside
        DB_LOAD, exit feature */
        fscanf(fp, "%d", &crim_being_loaded);

        #ifdef DEBUG_LOADING
        printf("\033[0;33m\n// DEBUGGING MODE FOR LOADING //\n");
        printf("DEBUG: i = %d, crim_being_loaded = %d\n", i, crim_being_loaded);
        if(crim_being_loaded == i){
            printf("DEBUG: MATCHED\n");
        }
        else if (crim_being_loaded != i){
            printf("DEBUG: NO MATCH\033[0m\n");
        }
        #endif

        if( crim_being_loaded != i/* || crim_being_loaded == '\n'*/)
        {
            #ifdef DEBUG_LOADING
            printf("\033[0;33mDEBUG: NO MATCH - crim_being_loaded = %d and i = %d\n\033[0m", crim_being_loaded, i);
            #endif
            return loaded;
        }
        else
        {
            char buffer[1000];

            #ifdef DEBUG_LOADING
            printf("\033[0;33mDEBUG: scanning i = %d into crimID = %d\033[0m\n", i, crim_being_loaded);
            #endif
            
            /* if there are criminals stored within DB_LOAD, being loading their data
            into the criminals[] array */

            /* scan in the first and last name and gender */
            fscanf(fp, "\n--%s | %s | %c", criminals[i].firstName, criminals[i].lastName, &criminals[i].physique.sex);
            /* debug */
            #ifdef DEBUG_LOADING
            printf("\033[0;33mDEBUG: loaded name and gender: %s %s %c\033[0m\n", criminals[i].firstName, criminals[i].lastName, criminals[i].physique.sex);
            #endif

            /* scan in DOB */
            fscanf(fp, "\n--DOB: %d/%d/%d :END_DOB", &criminals[i].dob.day, 
            &criminals[i].dob.month, &criminals[i].dob.year);

            /* print in height */
            fscanf(fp, "\n--HEIGHT: %lf :END_HEIGHT\n", &criminals[i].physique.height);

            /* scan in residential address */
            /* street no */
            fscanf(fp, "\n--RESADD_STREETNO: %d :END_RESADD_STREETNO\n", &criminals[i].resAddress.streetNumber);
            /* street name */
            fscanf(fp, "\n--RESADD_STREETNAME: %[^\n] :END_RESADD_STREETNAME\n", buffer);
            endBuff(buffer, criminals[i].resAddress.streetName);
            /* suburb */
            fscanf(fp, "\n--RESADD_SUBURB: %[^\n] :END_RESADD_SUBURB\n", buffer);
            endBuff(buffer, criminals[i].resAddress.suburb);
            /* state */
            fscanf(fp, "\n--RESADD_STATE: %[^\n] :END_RESADD_STATE\n", buffer);
            endBuff(buffer, criminals[i].resAddress.state);

            /* scan in criminal status */
            fscanf(fp, "\n--STATUS: %s :END_STATUS\n", buffer);
            endBuff(buffer, criminals[i].currentStatus);

            /* scan in occupation */
            fscanf(fp, "\n--OCCUP: %s :END_OCCUP\n", buffer);
            endBuff(buffer, criminals[i].occupation);

            /* print in num of charges */
            fscanf(fp, "\n--NUMCHARGES: %d :END_NUMCHARGES\n", &criminals[i].numCharges);

            if(criminals[i].numCharges>0)
            {
                int count=0;
                while(1)
                {
                    /* scanf number of offence */
                    fscanf(fp, "\n--OFFNUM: %d :END_OFFNUM\n", &count);

                    /* scanf in offence date */
                    fscanf(fp, "\n----OFFDATE: %d/%d/%d :END_OFFDATE\n", 
                    &criminals[i].crimHistory[count].occurrence.day, 
                    &criminals[i].crimHistory[count].occurrence.month, 
                    &criminals[i].crimHistory[count].occurrence.year);

                    /* scan in offence streetname */
                    fscanf(fp, "\n----OFFLOC_STREETNAME: %[^\n] :END_OFFLOC_STREETNAME",buffer);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: scanned in (streetname)buffer: '%s'\033[0m\n", buffer);
                    #endif

                    endBuff(buffer, criminals[i].crimHistory[count].crimLocation.streetName);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: ---- fixed (streetname)buffer: '%s'\033[0m\n", buffer);
                    #endif
                    
                    /* scan in offence suburb */
                    fscanf(fp, "\n----OFFLOC_SUBURB: %[^\n] :END_OFFLOC_SUBURB", buffer);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: scanned in (suburb)buffer: '%s'\033[0m\n", buffer);
                    #endif

                    endBuff(buffer, criminals[i].crimHistory[count].crimLocation.suburb);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: ---- fixed (suburb)buffer: '%s'\033[0m\n", buffer);
                    #endif
                    
                    /* scan in offence location */
                    fscanf(fp, "\n----DESCRIP: %[^\n] :END_DESCRIP", buffer);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: scanned in (descrip)buffer: '%s'\033[0m\n", buffer);
                    #endif

                    endBuff(buffer, criminals[i].crimHistory[count].descrip);

                    #ifdef DEBUG_LOADING
                    printf("\033[0;33mDEBUG: ---- fixed (descrip)buffer: '%s'\033[0m\n", buffer);
                    #endif

                    if(count==criminals[i].numCharges-1)
                    {
                        break;
                    }
                }
            }

            /* go scan the next criminal until no more criminals are found */
            loaded++;
            i++;

            #ifdef DEBUG_LOADING
            printf("\033[0;33mDEBUG: inside loop - loaded++ = %d\033[0m\n", loaded);
            #endif
        }
    }
    fclose(fp); /* close the file after done with it */

    #ifdef DEBUG_LOADING
    printf("\033[0;33mDEBUG: returning loaded = %d\033[0m\n", loaded);
    #endif
    
    return(loaded);
}



