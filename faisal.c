/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c faisal.c
*************************************************************************/

#include <stdio.h> /*snprintf*/
#include <string.h>
#include <stdlib.h>
#include <math.h> /*pow*/
#include "header.h"



/* faisal */
/*****************************************
 THIS HAS BEEN MOVED TO SEARCHDISPLAY
 ****************************************/
 
/*int searchName(criminal_t criminals [], int crimCount, int matchedNames[])
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
             checks between A - z 
            if( (nameToSearch[i]) - A < 0 || (nameToSearch[i]) - z >0)
            {
                 if there is an invalid char 
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
}*/




/* THIS HAS BEEN MOVED TO ADDCRIM.C
void addCrim(criminal_t criminals[], int crimCount)
{

    
        if(crimCount>MAX_NUM_OF_CRIMINALS)
        {
            printf("Database memory full.\nExiting...\n");
            return;
        }
        char fn[MAX_NAME_LEN];
        char ln[MAX_NAME_LEN];

        printf("\n");
        
        printf("--- Basic Information ---\n");

        printf("\nEnter first name > ");
        printf("\033[1;31m");
        scanf(" %s", fn);
        printf("\033[0m");
        strcpy(criminals[crimCount].firstName, fn);
        
        printf("Enter last name > ");
        printf("\033[1;31m");
        scanf(" %s", ln);
        printf("\033[0m");
        strcpy(criminals[crimCount].lastName, ln);

        printf("Enter sex [M/F] > ");
        scanf(" %c[\n]\n", criminals[crimCount].physique.sex);
        
        do {
            printf("Enter date of birth separated by space [dd mm yyyy] > ");
            scanf(" %d %d %d[\n]\n", 
            &criminals[crimCount].dob.day, 
            &criminals[crimCount].dob.month, 
            &criminals[crimCount].dob.year);
            
            int x = c

            if (x == 0) {
                printf("\n Date is invalid \n");
            }
        } while (x == 0);

        printf("\nStatus selection\n"
        "1. Fugitive\n"
        "2. Incarcerated\n"
        "3. Released\n");
        printf("Enter current status > ");
        int status;
        scanf(" %d[\n]\n", &status);
        switch(status)
        {
            case 1:
            {
                char inputStatus[] = "Fugitive";
                strcpy(criminals[crimCount].currentStatus, inputStatus);
                printf("Criminal is registered as a fugitive\n");
                break;
            }
            case 2:
            {
                char inputStatus[] = "Incarcerated";
                strcpy(criminals[crimCount].currentStatus, inputStatus);
                printf("Criminal is registered as incarcerated\n");
                break;
            }
            case 3:
            {
                char inputStatus[] = "Released";
                strcpy(criminals[crimCount].currentStatus, inputStatus);
                printf("Criminal has registered as released\n");
                break;
            }
            default:
                printf("Invalid input, please select from 1-3\n");
                break;
        }
        
        printf("\n--- Additional Information ---\n");

        if(skip()==1){
            return;
        };
        
        printf("\nEnter height > ");
        scanf(" %d[\n]\n", &criminals[crimCount].physique.height);
        
        skip();
        printf("Enter features > ");
        scanf(" %s[\n]\n", criminals[crimCount].physique.features);
        
        do{
        skip();
        printf("Enter Residential Address separated by space [StreetNumber StreetName Suburb  State] > ");
        scanf(" %d %s %s %s[\n]\n", 
        &criminals[crimCount].resAddress.streetNumber, 
        criminals[crimCount].resAddress.streetName, 
        criminals[crimCount].resAddress.suburb, 
        criminals[crimCount].resAddress.state);
        
        int y = addressIsValid(criminals[crimCount].resAddress);
         if (y == 0) {
                printf("\n Residential Address is invalid \n");
            }
        } while (y == 0);

        skip();
        printf("Enter occupation > ");
        scanf(" %s[\n]\n", criminals[crimCount].occupation);

        printf("\n--- Criminal History ---\n");

        int offenceNum = 0; 
        int breakout = 0;
        char addChoice;
        do
        {
            printf("\nCurrent number of registered offences under %s %s is %d", fn, ln, offenceNum);
            printf("\nWould you like to register an offence? [Y/N] > ");
            scanf("%c", &addChoice);
            switch(addChoice)
            {
                case 'Y':
                {
                    offenceNum++;

                    skip();
                    printf("\nEnter summary of offence #%d > ",offenceNum);
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory->charge);

                    do{
                    skip();
                    printf("Enter date of occurrence [dd mm yyyy] > ");
                    scanf(" %d %d %d[\n]\n", 
                    &criminals[crimCount].crimHistory[offenceNum].occurrence.day, 
                    &criminals[crimCount].crimHistory[offenceNum].occurrence.month, 
                    &criminals[crimCount].crimHistory[offenceNum].occurrence.year);
                    
                    int a = dateIsValid(criminal[crimCount]);
                    if (a == 0) {
                                printf("\n Occurrence date entry is invalid \n");
                            }
                     } while (a == 0);


                    do{
                    skip();
                    printf("Enter location of offence separated by space [StreetName Suburb] > ");
                    scanf(" %s %s[\n]\n",  
                    criminals[crimCount].crimHistory[offenceNum].crimLocation.streetName, 
                    criminals[crimCount].crimHistory[offenceNum].crimLocation.suburb);
                    
                    int z = addressIsValid(criminals[crimCount].crimLocation);
                    if (z == 0) {
                                printf("\n criminal Location is invalid \n");
                            }
                     } while (z == 0);


                    skip();
                    printf("Enter name of officer who charged criminal > "); 
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].officer);

                    skip();
                    printf("Enter brief description of offence > ");
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].descrip);

                    skip();
                    printf("Enter officer statement > ");
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].offStatement);

                    skip();
                    printf("Enter victim statement > ");
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].victStatement);

                    skip();
                    printf("Enter witness statement > ");
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].witnStatement);

                    skip();
                    printf("Enter names of individuals involved > ");
                    scanf(" %s[\n]\n", criminals[crimCount].crimHistory[offenceNum].whoInvolved);

                    break;
                }
                case 'N':
                {
                    breakout = 1;
                    break;
                }
                default:
                printf("Invalid input, please input Y or N");
            }
        }while(breakout != 1);

        
        
        
        
    
    
        criminals[crimCount].crimID = crimCount;
        
        skip();
        image_to_bin(crimCount);
        
        printf("\n");
        printf("Added criminal: \033[1;31mID# %02d\033[0m \033[1;31m%s %s\033[0m to the database with %d offences\n",crimCount, fn, ln, offenceNum);

        

}*/




/*https://arjunsreedharan.org/post/69303442896/how-to-find-the-size-of-an-array-in-c-without*/












/*MOVED TO BACKEND*/
/*******************************************************************************
 * This function extracts the headerfile information from the image
 *
 * inputs:
 * - FILE* image //binary file
 * - long offset //offset to find specific information
 * - int size //number of bytes
 * outputs:
 * - long //data about the image
*******************************************************************************/

long extract(FILE *image,long offset,int size){
    
    unsigned char *ptr;
    unsigned char temp='0';
    long value=0L;
    int i;

    
	ptr=&temp;

	fseek(image,offset,SEEK_SET);

    
	for(i=1;i<=size;i++){
	    fread(ptr,sizeof(char),1,image);
      
        value=(long)(value+(*ptr)*(pow(256,(i-1))));
    }
	 return value;
}



/*MOVED TO BACKEND*/
/*******************************************************************************
 * This function laods the .bmf file into a char array
 *
 * inputs:
 * - FILE* image 
 * - char file[] //name of image file
 * - char* image_array_p //array to store bmf metadata
 * outputs:
 * - none
*******************************************************************************/
void image_to_bin( int crimCount){


    FILE* image;
    FILE* image_bin;
    char* image_array_p;

    /*file path*/
    char PATH[] = "/home/images/";


    /*file name*/
    char file [50];
    printf("Enter criminal image file name\n");


    scanf("%s",file);
    /*adding file name to file path*/
    char image_path [100];
    sprintf(image_path,"%s%s",PATH,file);

    /*opening file and checking for error*/
    if((image=fopen(image_path,"rb"))==NULL){
        printf("Cant open the image.\nSystem is exiting.\n");
    }


    /*getting the size of the image*/
    unsigned long len = fsize(image_path);
    image_array_p = (char*) malloc((len+1)*sizeof(char));
    image=fopen(image_path,"rb");

    fseek(image,0,SEEK_SET);

    fread(image_array_p,len,1,image);

    int arraySize = len * 8;
    int* binaryArray ;
    binaryArray = (int*) malloc(arraySize*sizeof(int));
    binaryArray = convertCharToBit(len,image_array_p);
      #ifdef DEBUG
      int i;
      for(i=0;i<1000;i++){
        printf("%d",*(binaryArray+i));
      }
      #endif

    int crimCount1 = crimCount;
    char binfile [100];
    sprintf( binfile, "%s%02d.bin", PATH,crimCount1);
      #ifdef DEBUG
        printf("binfile: %s\n",binfile);
      #endif

    image_bin = fopen(binfile, "wb");
    fwrite(image_array_p,len,1,image_bin);



    #ifdef DEBUG
    int row,col,bpp,dataoffset;
    dataoffset=(int)extract(image,10,4);
    printf("dataoffset: %d\n", dataoffset);
	row=(int)extract(image,22,4);
    printf("number of rows: %d\n",row);
    col=(int)extract(image,18,4);
    printf("number of columns: %d\n",col);
    bpp=(int)extract(image,28,2);
    printf("bits per pixel: %d\n",bpp);
    #endif

    /*free(binfile);*/
    fclose(image_bin);
    fclose(image);
    return;
}



/*MOVED TO BACKEND*/
/*******************************************************************************
 * This function transforms the bin file back to .bmp format
 *
 * inputs:
 * - FILE *image_bin //binary image file
 * - FILE *new_image //bmf image file
 * - char binfile[] //name of binary file
 * - char* image_array_p // array to store bin data
 * outputs:
 * - none
*******************************************************************************/
void bin_to_image(int crimID){


    char PATH[] = "/home/images/";
    FILE* image_bin;
    FILE* new_image;
    char binfile[100];
    char* image_array_p =NULL;
    char new_image_file[100];
    sprintf(binfile,"%s%02d.bin",PATH,crimID);

      #ifdef DEBUG
      printf("binfile: %s\n",binfile);
      #endif
      
    strcpy(new_image_file,binfile);




    unsigned long len = fsize(binfile);
    image_array_p = (char*) malloc((len+1)*sizeof(char));
    image_bin=fopen(binfile,"rb");
    fseek(image_bin,0,SEEK_SET);
    fread(image_array_p,len,1,image_bin);

    sprintf(new_image_file,"%s%02d.bmp",PATH,crimID);
      #ifdef DEBUG
      printf("new_image_file: %s\n",new_image_file);
      #endif
    new_image = fopen(new_image_file,"wb");
    fwrite(image_array_p,len,1,new_image);
    fclose(new_image);
    return;
}


/*MOVED TO BACKEND*/
/*******************************************************************************
 * This function returns the size of the image in bytes
 *
 * inputs:
 * - char* file //image file
 * outputs:
 * - unsigned long //the number of bytes in the image.
*******************************************************************************/
unsigned long fsize(char* file){
    FILE* fp = fopen(file,"rb");
    fseek(fp,0,SEEK_END);
    unsigned long len =  (unsigned long)ftell(fp);
    rewind(fp);
    fclose(fp);
    return len;
} 

/*******************************************************************************
THIS HAS BEEN MOVED TO BACKEND
*******************************************************************************/
/*int skip(void)
{
    char skip;
    printf("(Enter '*' to skip feature)\n");
    scanf("%c", &skip);
  if (skip == '*')
        {
            return 1;
        }
  else 
        return 0;
    
    return 0;
}*/
