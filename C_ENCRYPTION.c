/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c encrypt.c


This file includes all encryption related functions
*************************************************************************/

#include <stdio.h> /*snprintf*/
#include <string.h>
#include <stdlib.h>
#include <math.h> /*pow*/
#include "H_MAIN.h"
#include "H_ENCRYPTION.h"
#include "H_IMAGES.h"



/*encryption*/
/* Author: Faisal */
int* convertCharToBit(int filesize, char* image_array_p){




    int arraySize = filesize * 8;

    int* binaryArray;
    binaryArray = (int*)malloc(arraySize*sizeof(int));
    if(binaryArray == NULL){
        printf("error\n");
        return 0;
    }


	char ch;


    int compare, temp, j=0,l,i;
	for (i=0;i < filesize;i++){
		ch = image_array_p[i];

  	    for (l = 7; l >= 0; l--){
            /* starting from the MSB determine if the bit is 1 or 0 by anding it and
            store it in bit.txt. i represents the current bit in 8 bit sequence. */
            temp = 1 << l;

            compare = (int)ch & temp;
            if (compare == 0){
                (binaryArray)[j]= 0;
                j++;
            }
  		    else{
                (binaryArray)[j]= 1;
                j++;
        }
  	}

  }


  return binaryArray;
}



/* Author: Faisal */
/*encryption*/
void encryption(int filesize,int dataoffset,char* image_array_p, FILE* encrypted_image, FILE* cipher){


  int IP[] =
    {
    	  58, 50, 42, 34, 26, 18, 10, 2,
    	  60, 52, 44, 36, 28, 20, 12, 4,
    	  62, 54, 46, 38, 30, 22, 14, 6,
    	  64, 56, 48, 40, 32, 24, 16, 8,
    	  57, 49, 41, 33, 25, 17,  9, 1,
    	  59, 51, 43, 35, 27, 19, 11, 3,
    	  61, 53, 45, 37, 29, 21, 13, 5,
    	  63, 55, 47, 39, 31, 23, 15, 7
    };

    int E[] =
    {
    	  32,  1,  2,  3,  4,  5,
    	   4,  5,  6,  7,  8,  9,
    	   8,  9, 10, 11, 12, 13,
    	  12, 13, 14, 15, 16, 17,
    	  16, 17, 18, 19, 20, 21,
    	  20, 21, 22, 23, 24, 25,
    	  24, 25, 26, 27, 28, 29,
    	  28, 29, 30, 31, 32,  1
    };
    int S1[4][16] =
    {
    		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    		{0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    		{4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    };

    int S2[4][16] =
    {
    	{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
    	 {3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
    	 {0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
    	{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    };

    int S3[4][16] =
    {
    	{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
    	{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
    	{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
    	 {1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
    };

    int S4[4][16] =
    {
    	 {7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
    	{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
    	{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
    	 {3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
    };

    int S5[4][16] =
    {
    	 {2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
    	{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
    	 {4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
    	{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
    };

    int S6[4][16] =
    {
    	{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
    	{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
    	 {9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
    	 {4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
    };

    int S7[4][16]=
    {
    	 {4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
    	{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
    	 {1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
    	 {6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
    };

    int S8[4][16]=
    {
    	{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
    	 {1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
    	 {7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
    	 {2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
    };

    int P[] =
    {
    	16,  7, 20, 21,
    	29, 12, 28, 17,
    	1, 15, 23, 26,
    	5, 18, 31, 10,
    	2,  8, 24, 14,
    	32, 27,  3,  9,
    	19, 13, 30,  6,
    	22, 11,  4, 25
    };

    int FP[] =
    {
    	  40, 8, 48, 16, 56, 24, 64, 32,
    	  39, 7, 47, 15, 55, 23, 63, 31,
    	  38, 6, 46, 14, 54, 22, 62, 30,
    	  37, 5, 45, 13, 53, 21, 61, 29,
    	  36, 4, 44, 12, 52, 20, 60, 28,
    	  35, 3, 43, 11, 51, 19, 59, 27,
    	  34, 2, 42, 10, 50, 18, 58, 26,
    	  33, 1, 41,  9, 49, 17, 57, 25
    };
    
    

    /*int arraySize = filesize * 8;*/


    /*printf("len: %d\n",len);
    printf("arraysize: %d\n",arraySize);*/
    int i=0,j=0;
    int subKeyArray [16][48];
    createKeys(subKeyArray);
    int numpadding = 8-(filesize % 8);
  
    for(i=0;i<numpadding;i++){
      strcat(image_array_p,"0");
    }  
    filesize = (filesize+numpadding);
    int* dataBitArray;
    dataBitArray = (int*)malloc(filesize*8*sizeof(int));
    dataBitArray = convertCharToBit(filesize,image_array_p);
    
    int arrayCount=0;
    int tempArray[64];
    int perm64Array[64];
    int perm48Array[48];
    int k=0;
    int lefthalftext[32];
    int righthalftext[32];
    int o=0;
    int p=0;
    int l;

    
    int firstXOR[48];
    int row[8][2];
    int column[8][4];
    int r=0, t=0, v=0, q = 0,u=0,c=0;
    int  temp;
    int S32[32];
    int perm32Array[32];
    int templefthalf[32];
    int SBOXFINAL[64];
    int CIPHERTEXT[64];
    int bin2dec;
    
    int w=0;
  

    /*buffer =(char*)malloc(arraySize*sizeof(char));*/
    
    



    
   
  
    u= ((filesize-dataoffset)/8);
    arrayCount = 8 *dataoffset;
    while(u>0){


        for ( i = 0; i < 64; i++){
            tempArray[i]=dataBitArray[arrayCount];
            arrayCount++;

        }

        for(i=0;i<64;i++){
            k = IP[i];
            perm64Array[i] = tempArray[k-1];

        }

        o=0;
        p=0;
        for(l=0;l<64;l++){
          if(l<32){
            lefthalftext[o] = perm64Array[l];
            o++;
          }
          else{
            righthalftext[p] = perm64Array[l];
            p++;
          }
        }
        #ifdef DEBUG_ENCRYPT
        printf("\n");
        printf("lefthalf: ");
        for ( i = 0; i < 32; i++){
          printf("%d",lefthalftext[i]);
        }
        printf("\n");
        printf("righthalf: ");
        for ( i = 0; i < 32; i++){
          printf("%d",righthalftext[i]);
        }
        #endif


        for(j=0;j<16;j++){


            for(i=0;i<48;i++){
                k = E[i];
                perm48Array[i] = righthalftext[k-1];

            }
            #ifdef DEBUG_ENCRYPT
            if(j==1){
            printf("\n");
            printf("perm48array: ");
            for ( i = 0; i < 48; i++){
              printf("%d",perm48Array[i]);
            }
            printf("\n");
            }
            #endif


            for( i =0;i<48;i++){

                firstXOR[i] = perm48Array[i]^subKeyArray[j][i];

                if(i == 47){
                    break;
                }
            }
            #ifdef DEBUG_ENCRYPT
            if(j==1){
            printf("\n");
            printf("firstXOR: ");
            for ( i = 0; i < 48; i++){
              printf("%d",firstXOR[i]);
            }
            printf("\n");
            }
            #endif
            w=0;
            for ( i = 0; i < 48; i += 6){
                row[w][0] = firstXOR[i];
                row[w][1] = firstXOR[i + 5];

                column[w][0] = firstXOR[i + 1];
                column[w][1] = firstXOR[i + 2];
                column[w][2] = firstXOR[i + 3];
                column[w][3] = firstXOR[i + 4];
                w++;
                if(i==48){
                    break;
                }
            }
            #ifdef DEBUG_ENCRYPT
            if(j==1){
            printf("\n");
            for ( l = 0; l < 8; l++){
              printf("\n");
              printf("column %d: ",l);

              for ( i = 0; i < 4; i++){
                printf("%d",column[l][i]);
              }
              printf("\n");
            }
            
            }
            #endif
            v=0;
            for(i=0;i<8;i++){

              r = row[i][0] * 2 + row[i][1];
            	c = 8 * column[i][0] + 4 * column[i][1] + 2 *column[i][2] + column[i][3];
              #ifdef DEBUG_ENCRYPT
              if(j==1){
              printf("r: %d c: %d \n",r,c);
              }                          
              #endif
            	if (i == 0){

            		t = S1[r][c];

              }
            	else if (i == 1){

            		t = S2[r][c];

              }
            	else if (i == 2){

            		t = S3[r][c];

              }
            	else if (i == 3){

            		t = S4[r][c];

              }
            	else if (i == 4){

            		t = S5[r][c];

              }
            	else if (i == 5){

            		t = S6[r][c];

              }
            	else if (i == 6){

            		t =S7[r][c];

              }
            	else if (i == 7){

            		t = S8[r][c];

              }
              #ifdef DEBUG_ENCRYPT
              if(j==1){
              printf("t: %d\n",t);
              }                          
              #endif
                
                for (l = 3; l >= 0; l--){

                    temp = t >> l;

                    
                    if (temp&1){
                        (S32)[v]= 1;
                        v++;
                    }
                    else{
                        (S32)[v]= 0;
                        v++;
                    }
                }
                
                
                k=0;
                
                for(q=0;q<32;q++){
                    k = P[q];
                    perm32Array[q] = S32[k-1];

                }




            }

            for(i=0;i<32;i++){
                templefthalf[i] = lefthalftext[i];


            }

            for(i=0;i<32;i++){
                lefthalftext[i] = righthalftext[i];


            }

            for(i=0;i<32;i++){
                righthalftext[i] = perm32Array[i]^templefthalf[i];
            }


            
            #ifdef DEBUG_ENCRYPT
                if(j==1){
                printf("\n");
                printf("S32: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",S32[i]);
                }
                printf("\n");
                printf("perm32array: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",perm32Array[i]);
                }
                printf("\n");
                printf("templefthalf: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",templefthalf[i]);
                }
                printf("\n");
                printf("righthalftext: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",righthalftext[i]);
                }
                printf("\n");
                printf("lefthalftext: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",lefthalftext[i]);
                }
                printf("\n");
                }                        
            #endif
           if(j==15){
                break;
            }
        }
         

        o=0;
        p=0;

        for(l=0;l<64;l++){
          if(l<32){
            SBOXFINAL[l]=righthalftext[o];
            o++;
          }
          else{
            SBOXFINAL[l]=lefthalftext[p];
            p++;
          }

        }

        k=0;
        for(i=0;i<64;i++){
            k = FP[i];
            CIPHERTEXT[i] = SBOXFINAL[k-1];

        }
        

        for(i=0;i<64;i+=8){
            bin2dec = 128*CIPHERTEXT[i]+64*CIPHERTEXT[i+1]+32*CIPHERTEXT[i+2]+16*CIPHERTEXT[i+3]+8*CIPHERTEXT[i+4]+4*CIPHERTEXT[i+5]+2*CIPHERTEXT[i+6]+CIPHERTEXT[i+7];
            

        	

          fprintf(cipher,"%c",bin2dec);
          fprintf(encrypted_image,"%c",bin2dec);

          #ifdef DEBUG_ENCRYPT
          char buffer[2];
          printf("bin2dec: %d\n",bin2dec);
          printf("buffer: %s\n",buffer);
          #endif
        }
     


        u--;

    }
    
    fclose(cipher);

    #ifdef DEBUG_ENCRYPT

   
    printf("\n");
    printf("dataBitArray: ");
    for(i=0;i<64;i++){
      printf("%d",dataBitArray[i]);
    }
    printf("\n");
    printf("perm64Array: ");
    for ( i = 0; i < 64; i++){
        printf("%d",perm64Array[i]);
    }
    
    printf("\n");
    printf("firstXOR: ");
    for ( i = 0; i < 48; i++){
        printf("%d",firstXOR[i]);
    }
    printf("\n");
    printf("\n");
    for ( j = 0; j < 8; j++){
      printf("\n");
      printf("column %d: ",j);

      for ( i = 0; i < 4; i++){
            printf("%d",column[j][i]);
      }
    }
    printf("\n");
    printf("S32: ");
    for ( i = 0; i < 32; i++){
        printf("%d",S32[i]);
    }
    printf("\n");
    printf("Cipher text: ");
      for(i=0;i<64;i++){
      printf("%d", CIPHERTEXT[i]);
      }
    printf("\n");
        
    #endif

    return;

}

/* Author: Faisal */
void createKeys(int sub48keys[16][48]){
    char file [] = "/home/keys.txt";
    FILE* fp;
    char keyArray[100];
    int lefthalf[28];
    int righthalf[28];
    int key56bits [56];

    int i=0;

    int sub56keys[16][56];
    int* keyBitArray;
    int PC1[] =
    {
    	  57, 49, 41, 33, 25, 17,  9,
    	   1, 58, 50, 42, 34, 26, 18,
    	  10,  2, 59, 51, 43, 35, 27,
    	  19, 11,  3, 60, 52, 44, 36,
    	  63, 55, 47, 39, 31, 23, 15,
    	   7, 62, 54, 46, 38, 30, 22,
    	  14,  6, 61, 53, 45, 37, 29,
    	  21, 13,  5, 28, 20, 12,  4
    };

    int PC2[] =
    {
    	  14, 17, 11, 24,  1,  5,
    	   3, 28, 15,  6, 21, 10,
    	  23, 19, 12,  4, 26,  8,
    	  16,  7, 27, 20, 13,  2,
    	  41, 52, 31, 37, 47, 55,
    	  30, 40, 51, 45, 33, 48,
    	  44, 49, 39, 56, 34, 53,
    	  46, 42, 50, 36, 29, 32
    };

    int SHIFTS[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    fp = fopen(file,"r");
    fseek(fp,0,SEEK_END);
    int len =  (int)ftell(fp);
    rewind(fp);
    /*printf("len: %d\n",len);*/
    fseek(fp,0,SEEK_SET);
    char ch;

    while(!feof(fp)){
      ch = fgetc(fp);
      keyArray[i++] = ch;
    }



    keyBitArray = (int*)malloc(64*sizeof(int));
    keyBitArray = convertCharToBit(len,keyArray);







    int k=0,j=0,n,o=0,p=0,l=0,x=0;
    
    for(i=0;i<56;i++){
    
      key56bits[i] = keyBitArray[PC1[i]-1];
      
      /*#ifdef DEBUG_CREATE_KEYS
      printf("k: %d\n",k);
      #endif
      if(keyBitArray[k]==1){
        key56bits[i] = 1;
      }
      else{
        key56bits[i] = 0;
      }*/
    }

    for(i=0;i<56;i++){
      if(i<28){
        lefthalf[o] = key56bits[i];
        o++;
      }
      else{
        righthalf[p] = key56bits[i];
        p++;
      }
    }



    int LMSB,RMSB;
    for(i=0;i<16;i++){
        n = SHIFTS[i];
        for(k=0;k<n;k++){
          LMSB = lefthalf[0];
          RMSB = righthalf[0];
          for(j=0;j<28;j++){
            lefthalf[j] = lefthalf[j+1];
            righthalf[j] = righthalf[j+1];
          }
          lefthalf[27] = LMSB;
          righthalf[27] = RMSB;
          o=0;
          p=0;
          for(l=0;l<56;l++){
            if(l<28){
              sub56keys[i][l]=lefthalf[o];
              o++;
            }
            else{
              sub56keys[i][l]=righthalf[p];
              p++;
            }

          }
        }

    }

    for ( j = 0; j < 16; j++){
  		for ( i = 0; i < 48; i++){
          x=PC2[i];
          sub48keys[j][i] = sub56keys[j][x-1];
  		}
    }


    #ifdef DEBUG_CREATE_KEYS
    int m=0;
    printf("keyBitArray:  ");
    for(n=0;n<64;n++){

      printf("%d",keyBitArray[n]);
    }
    printf("\n");
    printf("56 bit key: ");
    for(i=0;i<56;i++){
      printf("%d",key56bits[i]);
    }
    printf("\n");
    printf("left half:  ");
    for(n=0;n<28;n++){

      printf("%d",lefthalf[n]);
    }
    printf("\n");
    printf("right half: ");
    for(m=0;m<28;m++){

      printf("%d",righthalf[m]);
    }
    printf("\n");
    
    for ( j = 0; j < 16; j++){
  		printf("\n");
  		printf("Sub56key %d: ",j);

  		for ( i = 0; i < 56; i++){
  					printf("%d",sub56keys[j][i]);
  		}
  	}
    printf("\n");
    for ( j = 0; j < 16; j++){
  		printf("\n");
  		printf("Sub48key %d: ",j);

  		for ( i = 0; i < 48; i++){
  					printf("%d",sub48keys[j][i]);
  		}
  	}
    printf("\n");

    #endif

    free(keyBitArray);


    return ;
}

void decryption(char* image_array_p,int crimID,int dataoffset, int filesize,FILE* new_image){


    int IP[] =
    {
    	  58, 50, 42, 34, 26, 18, 10, 2,
    	  60, 52, 44, 36, 28, 20, 12, 4,
    	  62, 54, 46, 38, 30, 22, 14, 6,
    	  64, 56, 48, 40, 32, 24, 16, 8,
    	  57, 49, 41, 33, 25, 17,  9, 1,
    	  59, 51, 43, 35, 27, 19, 11, 3,
    	  61, 53, 45, 37, 29, 21, 13, 5,
    	  63, 55, 47, 39, 31, 23, 15, 7
    };

    int E[] =
    {
    	  32,  1,  2,  3,  4,  5,
    	   4,  5,  6,  7,  8,  9,
    	   8,  9, 10, 11, 12, 13,
    	  12, 13, 14, 15, 16, 17,
    	  16, 17, 18, 19, 20, 21,
    	  20, 21, 22, 23, 24, 25,
    	  24, 25, 26, 27, 28, 29,
    	  28, 29, 30, 31, 32,  1
    };
    int S1[4][16] =
    {
    		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
    		{0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
    		{4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
    		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    };

    int S2[4][16] =
    {
    	{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
    	 {3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
    	 {0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
    	{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    };

    int S3[4][16] =
    {
    	{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
    	{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
    	{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
    	 {1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
    };

    int S4[4][16] =
    {
    	 {7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
    	{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
    	{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
    	 {3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
    };

    int S5[4][16] =
    {
    	 {2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
    	{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
    	 {4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
    	{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
    };

    int S6[4][16] =
    {
    	{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
    	{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
    	 {9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
    	 {4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
    };

    int S7[4][16]=
    {
    	 {4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
    	{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
    	 {1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
    	 {6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
    };

    int S8[4][16]=
    {
    	{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
    	 {1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
    	 {7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
    	 {2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
    };

    int P[] =
    {
    	16,  7, 20, 21,
    	29, 12, 28, 17,
    	1, 15, 23, 26,
    	5, 18, 31, 10,
    	2,  8, 24, 14,
    	32, 27,  3,  9,
    	19, 13, 30,  6,
    	22, 11,  4, 25
    };

    int FP[] =
    {
    	  40, 8, 48, 16, 56, 24, 64, 32,
    	  39, 7, 47, 15, 55, 23, 63, 31,
    	  38, 6, 46, 14, 54, 22, 62, 30,
    	  37, 5, 45, 13, 53, 21, 61, 29,
    	  36, 4, 44, 12, 52, 20, 60, 28,
    	  35, 3, 43, 11, 51, 19, 59, 27,
    	  34, 2, 42, 10, 50, 18, 58, 26,
    	  33, 1, 41,  9, 49, 17, 57, 25
    };
    
    
    
  
    int arraySize = filesize * 8;


    /*printf("len: %d\n",len);
    printf("arraysize: %d\n",arraySize);*/
    int i=0,j=0;
    int subKeyArray [16][48];
    createKeys(subKeyArray);
    
    int* dataBitArray;
    dataBitArray = (int*)malloc(arraySize*sizeof(int));
    dataBitArray = convertCharToBit(filesize,image_array_p);
    
    int arrayCount=0;
    int tempArray[64];
    int perm64Array[64];
    int perm48Array[48];
    int k=0;
    int lefthalftext[32];
    int righthalftext[32];
    int o=0;
    int p=0;
    int l;

  
    int firstXOR[48];
    int row[8][2];
    int column[8][4];
    int r=0, t=0, v=0, q = 0,u=0,c=0;
    int  temp;
    int S32[32];
    int perm32Array[32];
    int templefthalf[32];
    int SBOXFINAL[64];
    int CIPHERTEXT[64];
    int bin2dec;
    
    int w=0;
  

    /*buffer =(char*)malloc(arraySize*sizeof(char));*/
  

    

    
    arrayCount = dataoffset*8;
    u= ((filesize-dataoffset)/8);
    while(u>0){


        for ( i = 0; i < 64; i++){
            tempArray[i]=dataBitArray[arrayCount];
            arrayCount++;

        }

        for(i=0;i<64;i++){
            k = IP[i];
            perm64Array[i] = tempArray[k-1];

        }
        o=0;
        p=0;
        for(l=0;l<64;l++){
          if(l<32){
            lefthalftext[o] = perm64Array[l];
            o++;
          }
          else{
            righthalftext[p] = perm64Array[l];
            p++;
          }
        }
        #ifdef DEBUG_DECRYPT
        printf("\n");
        printf("lefthalf: ");
        for ( i = 0; i < 32; i++){
          printf("%d",lefthalftext[i]);
        }
        printf("\n");
        printf("righthalf: ");
        for ( i = 0; i < 32; i++){
          printf("%d",righthalftext[i]);
        }
        #endif


        for(j=0;j<16;j++){


            for(i=0;i<48;i++){
                k = E[i];
                perm48Array[i] = righthalftext[k-1];

            }
            #ifdef DEBUG_DECRYPT
            if(j==1){
            printf("\n");
            printf("perm48array: ");
            for ( i = 0; i < 48; i++){
              printf("%d",perm48Array[i]);
            }
            printf("\n");
            }
            #endif


            for( i =0;i<48;i++){

                firstXOR[i] = perm48Array[i]^subKeyArray[15-j][i];

                if(i == 47){
                    break;
                }
            }
            #ifdef DEBUG_DECRYPT
            if(j==1){
            printf("\n");
            printf("firstXOR: ");
            for ( i = 0; i < 48; i++){
              printf("%d",firstXOR[i]);
            }
            printf("\n");
            }
            #endif
            w=0;
            for ( i = 0; i < 48; i += 6){
                row[w][0] = firstXOR[i];
                row[w][1] = firstXOR[i + 5];

                column[w][0] = firstXOR[i + 1];
                column[w][1] = firstXOR[i + 2];
                column[w][2] = firstXOR[i + 3];
                column[w][3] = firstXOR[i + 4];
                w++;
                if(i==48){
                    break;
                }
            }
            #ifdef DEBUG_DECRYPT
            if(j==1){
            printf("\n");
            for ( l = 0; l < 8; l++){
              printf("\n");
              printf("column %d: ",l);

              for ( i = 0; i < 4; i++){
                printf("%d",column[l][i]);
              }
              printf("\n");
            }
            
            }
            #endif
            v=0;
            for(i=0;i<8;i++){

              r = row[i][0] * 2 + row[i][1];
            	c = 8 * column[i][0] + 4 * column[i][1] + 2 *column[i][2] + column[i][3];
              #ifdef DEBUG_DECRYPT
              if(j==1){
              printf("r: %d c: %d \n",r,c);
              }                          
              #endif
            	if (i == 0){

            		t = S1[r][c];

              }
            	else if (i == 1){

            		t = S2[r][c];

              }
            	else if (i == 2){

            		t = S3[r][c];

              }
            	else if (i == 3){

            		t = S4[r][c];

              }
            	else if (i == 4){

            		t = S5[r][c];

              }
            	else if (i == 5){

            		t = S6[r][c];

              }
            	else if (i == 6){

            		t =S7[r][c];

              }
            	else if (i == 7){

            		t = S8[r][c];

              }
              #ifdef DEBUG_DECRYPT
              if(j==1){
              printf("t: %d\n",t);
              }                          
              #endif
                
                for (l = 3; l >= 0; l--){

                    temp = t >> l;

                    
                    if (temp&1){
                        (S32)[v]= 1;
                        v++;
                    }
                    else{
                        (S32)[v]= 0;
                        v++;
                    }
                }
                
                
                k=0;
                
                for(q=0;q<32;q++){
                    k = P[q];
                    perm32Array[q] = S32[k-1];

                }




            }

            for(i=0;i<32;i++){
                templefthalf[i] = lefthalftext[i];


            }

            for(i=0;i<32;i++){
                lefthalftext[i] = righthalftext[i];


            }

            for(i=0;i<32;i++){
                righthalftext[i] = perm32Array[i]^templefthalf[i];
            }


            
            #ifdef DEBUG_DECRYPT
                if(j==1){
                printf("\n");
                printf("S32: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",S32[i]);
                }
                printf("\n");
                printf("perm32array: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",perm32Array[i]);
                }
                printf("\n");
                printf("templefthalf: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",templefthalf[i]);
                }
                printf("\n");
                printf("righthalftext: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",righthalftext[i]);
                }
                printf("\n");
                printf("lefthalftext: ");
                for ( i = 0; i < 32; i++){
                 printf("%d",lefthalftext[i]);
                }
                printf("\n");
                }                        
            #endif
           if(j==15){
                break;
            }
        }
         

        o=0;
        p=0;

        for(l=0;l<64;l++){
          if(l<32){
            SBOXFINAL[l]=righthalftext[o];
            o++;
          }
          else{
            SBOXFINAL[l]=lefthalftext[p];
            p++;
          }

        }

        k=0;
        for(i=0;i<64;i++){
            k = FP[i];
            CIPHERTEXT[i] = SBOXFINAL[k-1];

        }
        

        for(i=0;i<64;i+=8){
          bin2dec = 128*CIPHERTEXT[i]+64*CIPHERTEXT[i+1]+32*CIPHERTEXT[i+2]+16*CIPHERTEXT[i+3]+8*CIPHERTEXT[i+4]+4*CIPHERTEXT[i+5]+2*CIPHERTEXT[i+6]+CIPHERTEXT[i+7];
            


          fprintf(new_image,"%c",bin2dec);

          #ifdef DEBUG_DECRYPT
          char buffer[2];
         	sprintf(buffer,"%x",bin2dec);
          printf("bin2dec: %d\n",bin2dec);
          printf("buffer: %s\n",buffer);
          #endif
        }
        


        u--;

    }
    
    fclose(new_image);

    #ifdef DEBUG_DECRYPT

   
    printf("\n");
    printf("dataBitArray: ");
    for(i=0;i<64;i++){
      printf("%d",dataBitArray[i]);
    }
    printf("\n");
    printf("perm64Array: ");
    for ( i = 0; i < 64; i++){
        printf("%d",perm64Array[i]);
    }
    
    printf("\n");
    printf("firstXOR: ");
    for ( i = 0; i < 48; i++){
        printf("%d",firstXOR[i]);
    }
    printf("\n");
    printf("\n");
    for ( j = 0; j < 8; j++){
      printf("\n");
      printf("column %d: ",j);

      for ( i = 0; i < 4; i++){
            printf("%d",column[j][i]);
      }
    }
    printf("\n");
    printf("S32: ");
    for ( i = 0; i < 32; i++){
        printf("%d",S32[i]);
    }
    printf("\n");
    printf("Cipher text: ");
      for(i=0;i<64;i++){
      printf("%d", CIPHERTEXT[i]);
      }
    printf("\n");
        
    #endif

    return;



}

