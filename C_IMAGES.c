#include <stdio.h> /*fclose, fopen, fread, fwrite, fseek, ftell, sprintf, scanf, printf*/
#include <stdlib.h> /*malloc, */
#include <string.h> 
#include <math.h> /*pow*/

#include "H_MAIN.h"
#include "H_IMAGES.h"
#include "H_ENCRYPTION.h"


/* Author: Faisal */
/* for images*/
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
long extract(FILE *image,long offset,int size)
{
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


/* Author: Faisal */
/* for images*/
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
    
    char* image_array_p;

    /*file path*/
    char PATH[] = "/home/images/";


    /*file name*/
    char file [50];
    printf("To upload an image, drag or upload an image file into the folder called 'images'.\n");
    printf("Then enter the filename of the image in the format \033[0;33m<filename>.<filetype>\033[0m\n(e.g. image.bmp) [BMP preffered] > ");
    scanf("%s",file);

    /*adding file name to file path*/
    char image_path [100];
    sprintf(image_path,"%s%s",PATH,file);

    /*opening file and checking for error*/
    if((image=fopen(image_path,"rb"))==NULL){
        printf("ERROR: No image found. Image upload failed.\n");
    }


    /*getting the size of the image*/
    unsigned long filesize = fsize(image_path);
    image_array_p = (char*) malloc((filesize+1)*sizeof(char));
    image=fopen(image_path,"rb");

    fseek(image,0,SEEK_SET);

    fread(image_array_p,filesize,1,image);

   /*Storing image properties for encrypted bmp image*/
    int dataoffset;
    dataoffset=(int)extract(image,10,4);
    FILE* encrypted_image;
    char encrypted_image_file[100];
    sprintf(encrypted_image_file,"%sencrypt%02d.bmp",PATH,crimCount);
    encrypted_image = fopen(encrypted_image_file,"ab");
    fwrite(image_array_p,dataoffset,1,encrypted_image);

    
      

   /*storing image properties  in binfile*/
    char binfile [100];
    sprintf( binfile, "%s%02d.bin", PATH,crimCount);
    FILE* cipher;
    cipher = fopen(binfile,"ab");
    fwrite(image_array_p,dataoffset,1,cipher);

    encryption(filesize,dataoffset,image_array_p, encrypted_image,cipher);
    

    

    
    
    
    #ifdef DEBUG_IMAGES
    printf("binfile: %s\n",binfile);
    int row,col,bpp;
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
   
    fclose(image);
    return;
}


/* Author: Faisal */
/* for images*/
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
    FILE* encrypted_image_file; 
   
  
    char encrypted_image_path[100];
    char* image_array_p =NULL;
    char new_image_file[100];
    sprintf(encrypted_image_path,"%sencrypt%02d.bmp",PATH,crimID);

      #ifdef DEBUG_IMAGES
      printf("encryptbmp: %s\n",encrypted_image_path);
      #endif
      
    




    int filesize = fsize(encrypted_image_path);
    image_array_p = (char*) malloc((filesize+1)*sizeof(char));
    encrypted_image_file=fopen(encrypted_image_path,"rb");
    fseek(encrypted_image_file,0,SEEK_SET);
    fread(image_array_p,filesize,1,encrypted_image_file);

    sprintf(new_image_file,"%s%02d.bmp",PATH,crimID);

    FILE* new_image;
    new_image = fopen(new_image_file,"ab");
    int dataoffset;
    dataoffset=(int)extract(encrypted_image_file,10,4);
    
    fwrite(image_array_p,dataoffset,1,new_image);


    decryption(image_array_p,crimID,dataoffset,filesize,new_image);
  
    

    
    
      #ifdef DEBUG_IMAGES
      printf("new_image_file: %s\n",new_image_file);
      
      #endif
  return;    
}


/* Author: Faisal */
/*images*/
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
