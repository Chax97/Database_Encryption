/* to check if your code COMPILES (not BUILD a .out) type the following into the terminal:

gcc -Wall -Werror -ansi -lm -c C_COMPRESION.c
*************************************************************************/
/* some notes:
- ASCII values are between 0 - 127 
https://www.sciencebuddies.org/science-fair-projects/references/ascii-table
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "H_COMPRESSION.h"

/* finds and returns the smaller sub-tree in the forrest */
/* finds and returns the index of the smaller subtree in a forest */
/* pass the pointer to an array and manipulates its elements */
int getSmaller(node_t* nodearray[], int indexcmp)
{
    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("\n---GETSMALLER DEBUGGING---\n");
    printf("passed indexcmp=%d\n", indexcmp);
    printf("\033[0m"); 
    #endif 
    int smaller;
    int index=0;

    /*if the frequency of a node structure is non existent (hasn't been assigned?) go to the next node structure in the array*/
    while(nodearray[index]->freq == -1)
    {
        index++;
    }
    smaller=index;

    /* if the index we are looking at == the index we are comparing with, go to the next index*/
    /* then continue filtering through unassigned frequency structures */
 
    if(index==indexcmp)
    {
        #ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("if(index==indexcmp) was triggered with index=%d and smaller=%d\n", index, smaller);
        printf("\033[0m"); 
        #endif 

        index++;
        while(nodearray[index]->freq == -1)
        {
            index++;
        }
        smaller=index;

        #ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("inside if(index==indexcmp) index=%d - smaller=%d\n", index, smaller);
        printf("\033[0m"); 
        #endif
    }

    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("before triggereing for loop, we have following values: index=%d, indexcmp=%d, smaller=%d\n", index, indexcmp, smaller);
    printf("\033[0m"); 
    #endif
 
    /* at this point, smaller has been initliased to be the index of some structure that *has* as frequency */

    /* filter through the indexes */
    for(index=0; index<NO_OF_CHARS; index++)
    {
        /*#ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("index in for loop=%d\n", index);
        printf("\033[0m"); 
        #endif */
        /* if unassigned frequency */
        if(nodearray[index]->freq == -1)
        {
            /* go to the next index */
            continue;
        }

        /* if index = index we are comparing with */
        if(index == indexcmp)
        {
            /* go to the next index */
            continue;
        }

        /* compare frequency values of node with index i and node with index smaller (starting from the initialised smaller index, then the updated smaller indexes) */
        /* if the ith frequency is < the smaller-th frequency, update smaller to = i */
        if(nodearray[index]->freq < nodearray[smaller]->freq)
        {
            smaller = index;
        }
        /* repeat the for loop, checking against every index, except a specified index - indexcmp, until the index with the smallest frequency is found */
    }

    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("after for loop, we have following values: index=%d, indexcmp=%d, smaller=%d\n", index, indexcmp, smaller);
    printf("\033[0m"); 
    #endif

    return smaller;
}

/* this function builds the huffman tree and returns the address of the root (top of tree) */
/* pass a pointer of a pointer */
void makeHuffmanTree(node_t** tree, int freq[], int arSz)
{
    /* create a temporary node pointer*/
    node_t* temp;
    /* create an array of node pointers (array of subtrees) */
    node_t* nodearray[NO_OF_CHARS];
    /* integer index for looping */
    /* integer subTrees denoting how many subTrees there are */
    int index, subTrees = NO_OF_CHARS;
    int smallone, smalltwo;

    /* initialize every node of the array */
    /* initilaize all of them with no children */
    for(index=0;index<NO_OF_CHARS;index++)
    {
        /* allocate some memory for the array entry */
        nodearray[index]=(node_t*)malloc(sizeof(node_t));
        /* use the freq[] array to fill in the frequencies for each node */
        nodearray[index]->freq=freq[index];
        /* denote the letter as the i'th letter */
        nodearray[index]->ch=index;
        /* initliase left and right children as NULL */
        nodearray[index]->left = NULL;
        nodearray[index]->right = NULL;
    }
    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("\n---MAKEHUFFMAN DEBUGGING---\n");
    int i;
    printf("nodearray after initialization:\n");
    for(i=0;i<NO_OF_CHARS;i++)
    {
        printf("nodearray[%d] address=%p | ->ch=%d | ->freq=%d\n",i, nodearray[i], nodearray[i]->ch, nodearray[i]->freq);
    }
    printf("\033[0m"); 
    #endif 


    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("inside while loop:\n");
    printf("\033[0m"); 
    #endif 

    /* generate huffman tree */
    while(subTrees>1)
    {
        /* first step: get the node with the smallest frequency */
        smallone = getSmaller(nodearray, -1); /* index of node with smallest freq */
        /* second step: get the node with the second smallest frequency by passing smallone to getSmaller */
        smalltwo = getSmaller(nodearray, smallone); /* index of node with 2nd smallest freq */
        /* now we have the indexes for the nodes to which the smallest and 2nd smallest frequencies belong to */

        #ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("\nback in the while loop in MAKEHUFFMAN\nreturned smallone = %d then ", smallone);
        printf("returned smalltwo = %d\n", smalltwo);
        printf("\033[0m"); 
        #endif

        /* intialize the temp pointer to point to nodearray[smallone]*/
        temp = nodearray[smallone];

        /* malloc nodearray[smallone] (the first node in the array of subtrees) again - this makes it point to a new fresh block of memory, and temp preserves the old data it held */
        /* initialize nodearray[smallone] such that:
            - freq = freq(left) + freq(right), where
            - left = 2nd smallest freq node (larger child freq)
            - right = smallest freq node (smaller child freq)
            - letter = arbitrary value (outside letter range)
        */
        nodearray[smallone]=(node_t*)malloc(sizeof(node_t));
        nodearray[smallone]->freq=nodearray[smalltwo]->freq+temp->freq;
        nodearray[smallone]->ch=-10; /* flag value to set node as NOT a leaf */
        nodearray[smallone]->left=nodearray[smalltwo]; /* left child = larger freq */
        nodearray[smallone]->right=temp; /* right child = smaller freq */
        /* flag the child node as freq = -1 so that getsmaller knows it's a child and to to ignore it */
        nodearray[smalltwo]->freq=-1;

        #ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("smallone=%d - ", smallone);
        printf("nodearray[smallone] add=%p | freq=%d | ch=%d | ->left=%p | ->right=%p\n", nodearray[smallone], nodearray[smallone]->freq, nodearray[smallone]->ch, nodearray[smallone]->left, nodearray[smallone]->right);
        printf("smalltwo=%d - ", smalltwo);
        printf("nodearray[smalltwo] add=%p | freq=%d | ch=%d | ->left=%p | ->right=%p\n", nodearray[smalltwo], nodearray[smalltwo]->freq, nodearray[smalltwo]->ch, nodearray[smalltwo]->left, nodearray[smalltwo]->right);
        printf("temp add=%p\n", temp);
        printf("\033[0m"); 
        #endif 

        /* decrement subtrees, and continue while loop - building huffman tree */
        subTrees--;
    }
    /* return pointer to the root of the tree */
    *tree = nodearray[smallone];

    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    int j;
    printf("nodearray after makeHuffmanTree:\n");
    for(j=0;j<NO_OF_CHARS;j++)
    {
        printf("nodearray[%d] address=%p | ->ch=%d | ->freq=%d | ->left=%p | ->right=%p\n",j, nodearray[j], nodearray[j]->ch, nodearray[j]->freq, nodearray[j]->left, nodearray[j]->right);
    }
    printf("*tree=%p\n", *tree);
    printf("\033[0m"); 
    #endif 
}

/* this function makes and fills out the onetwocodes[] array with the code strings for each respective letters. NOTE: 1 = binary 0 and 2 = binary 1 - for arithmetic purposes */
void makeCodes(long onetwocodes[], node_t *nodeprobe, long code)
{
    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("\n---MAKECODES FUNCTION DEBUGGING---\n");
    printf("*nodeprobe=%p | ->left=%p | ->right=%p\n", nodeprobe, nodeprobe->left, nodeprobe->right);
    printf("\033[0m"); 
    #endif 

    /* if nodeprobe points to a letter (ch) with a value less than NO_OF_CHARS */
    /* if the subtree points to a valid char, write a code for it */
    int probe = nodeprobe->ch; 

    #ifdef DEBUG_COMPRESSION 
    printf("\033[0;33m");
    printf("probe=%d\n", probe);
    printf("\033[0m"); 
    #endif

    if(probe>=0 && probe<=NO_OF_CHARS)
    {
        #ifdef DEBUG_COMPRESSION 
        printf("\033[0;33m");
        printf("nodeprobe->ch=%d\n", nodeprobe->ch);
        printf("\033[0m"); 
        #endif

        int index = nodeprobe->ch;
        onetwocodes[index] = code;
    }
    /* recursion for going down the tree */
    else 
    {
        makeCodes(onetwocodes, nodeprobe->left, code*10+1); /* left = 1 */
        makeCodes(onetwocodes, nodeprobe->right, code*10+2); /* right = 2 */
    }
    return; 
}

void compressFile(long huffmanCodes[], char letters[])
{
    char bitvalue;
    char ch;
    char binCode = 0;
    int code;
    int codelength;
    int bitsLeft = 8;
    int status=0;

    /* open the input text file */
	FILE* inputp = NULL; /* file stream */
	inputp = fopen(INPUT_FILE_NAME, "r");
	if (inputp == NULL){
		printf("input file error\n");
		return;
	}
    
    /* open the output binary file */
	FILE* outputp = NULL; /* file stream */
	outputp = fopen(OUTPUT_FILE_NAME, "wb");
	if (outputp == NULL){
		printf("output file error\n");
		return;
	}

    #ifdef DEBUG_COMPRESSFILE
    int charsRead=0;
    #endif

    /* scan every character from the beginning to the end of file */
    /* fgetc(inputp) returns -1 for EOF (even though it's not the ascii code for it) */
    while ((ch=fgetc(inputp))!=-1)
    {
        #ifdef DEBUG_COMPRESSFILE
        printf("DEBUG: reading char %d - letter: %c --> ", charsRead, ch);
        #endif

        /* search the array of letters for matching letter */
        int index=0;
        int match;
        while(index<NO_OF_CHARS)
        {
            if(letters[index]==ch)
            {
                #ifdef DEBUG_COMPRESSFILE
                printf("found match letters[%d]=%c ",index, letters[index]);
                printf("| match = index = %d \n", index);
                #endif

                match=index;
                break;
            }
            else
            {
                match=-1;
            }
            index++;
        }
       
        #ifdef DEBUG_COMPRESSFILE
        charsRead++;
        #endif
    
        /* if no match was found, go to the next character and repeat */
        if(match==-1)
        {
            status = 1;
            break;
        }
        /* now we have the index of the matching letter */
        if (ch==32) /* if space - get data for space */
        {
            codelength = (log10(huffmanCodes[26])+1);
            code = huffmanCodes[26];
        }
        else
        {
            /* using the 1 2 arithmetic implemented in makeHuffman, use math to be able to make it into bit data */
            /* get length of the matched code */
            codelength=(log10(huffmanCodes[match])+1);   /*eg, code = 11, length = 2 */
            code = huffmanCodes[match];                  /*eg, code = 11 */
        }

        /* because we can only write 1 byte (8 bits) of data to a binary file at any one time, we have to combine the huffmancodes bit by bit until an 8bit string is formed, and then we can write that into the binary file */
        /* the following is a process based on the 1 2 arithmetic to write either a 1 or a 0 into the 8 bit 
        code that is to be written into the output file */
        while (codelength>0)
        {
            #ifdef DEBUG_DECOMPFILE
            printf("DEBUG: \033[0;35mcode = %d\033[0m | ", code);
            #endif
                
                                                        /* the comments below is an example of the process on code = 11 */
            bitvalue = code % 10 - 1;   /* % returns remainder-1 eg: 11%10-1 = 1-1=0 -> bit = 00000000*/
            code /= 10;                 /* code = code/10 eg: code = 11/10 = 1 -> code = 00000001*/
            binCode = binCode | bitvalue;  /* binary OR the binCode and bitvalue -> code = 00000001 */
            bitsLeft--;                 /* bitsleft = 7 */
            codelength--;               /* length = 2-1 = 1 */

            #ifdef DEBUG_DECOMPFILE
            printf("\033[0;33mafter iteration: bitvalue = \033[1;35m%d\033[0m | binCode = %d | bitsLeft = %d\033[0m\n", bitvalue, binCode, bitsLeft);
            #endif
            
            /* once binCode has 8 bits of information following the huffman code, write that into the binary file */
            if (bitsLeft==0)
            {   
                #ifdef DEBUG_DECOMPFILE
                printf("DEBUG: \033[1;35m>>>>>> fputc: binCode = %d\033[0m\n", binCode);
                #endif

                fputc(binCode,outputp);
                /* reset binCode and bitsleft */
                binCode = 0;
                bitsLeft = 8;
            }
            /* binary shift the binCode by 1 so that the next bit can be modified to the huffman code */
            binCode = binCode << 1;     /* shift binary left eg: binCode = 000000010*/
        }
    }
    /* this code is written incase the final huffman code doesn't take up a full 8 bits that is required to 
    write into a binary file */
    if (bitsLeft!=8){
        binCode = binCode << (bitsLeft-1);
        fputc(binCode,outputp);
        #ifdef DEBUG_DECOMPFILE
        printf("DEBUG: \033[1;35m>>>>>> fputc: binCode = %d\033[0m\n", binCode);
        #endif
    }

    /*print details of compression on the screen*/
    /* calculate file sizes */
    fseek(inputp,0,SEEK_END);
    int inSize=ftell(inputp);
    fseek(outputp,0,SEEK_END);
    int outSize=ftell(outputp);
    float ratio = ((double)outSize/(double)inSize)*100;

    if(status==1)
    {
        printf("\033[1;31m<<< COMPRESSION FAILED >>>\033[0m\n");
        printf("ERROR: Unknown character '%c' is preventing compression. The character is\n", ch);
        printf("not defined with a Huffman code. Please remove problematic character from\n"
               "file if you wish to compress.\n");
        return;
    }
    printf("\033[1;30m<<< COMPRESSED SUCCESSFULLY >>>\033[0m\n");
    printf("Original DATABASE filesize: \033[1;36m%d bytes\033[0m\n", inSize);
    printf("Compressed DATABASE filesize: \033[1;36m%d bytes\033[0m\n", outSize);
    printf("\033[1;32mDATABASE file was compressed to \033[1;36m%.2f%%\033[0m\033[1;32m of its original size.\033[0m\n", ratio);

    fclose(inputp);
    fclose(outputp);

    /*remove(INPUT_FILE_NAME);*/
}

void decompFile(node_t* tree, char letters[])
{
    /* open the file to decompress */
	FILE* inputp = NULL; /* file stream */
	inputp = fopen(OUTPUT_FILE_NAME, "rb");
	if (inputp == NULL){
		printf("input file error\n");
		return;
	}
    
    /* open the file to print the decompressed text */
	FILE* outputp = NULL; /* file stream */
	outputp = fopen(DECOMP_FILE_NAME, "w");
	if (outputp == NULL){
		printf("output file error\n");
		return;
	}

    /* define a probe node pointer */
    node_t* probe = NULL;
    /* assign it to point to the root of the huffman tree */
    probe = tree;

    #ifdef DEBUG_DECOMPFILE
    printf("DEBUG: Address of tree = %p\n", tree);
    #endif

    char ch;
    /* define two chars - one for the bit being scanned (bit) and one to 
    act as a bitmask to use for bitwise operations*/
    char bit;
    char bitmask = 00000001 << 7; /* bitwise left by 7 so that bitmask = 0b10000000 */
    int probeCh;
    int i;

    #ifdef DEBUG_DECOMPFILE
    printf("DEBUG: bitmask = %d\n", bitmask);
    #endif

    /* begin reading every character from the input file till the EOF */
    while((ch=fgetc(inputp))!=EOF)
    {
        #ifdef DEBUG_DECOMPFILE
        printf("DEBUG: \033[1;35mch=fgetc(inputp) = %d\033[0m\n", ch);
        #endif

        /* read the return value from fgetc */
        /* fgetc returns a whole byte (8 bits) of 1's and 0's */
        for(i=0; i<8; i++)
        {            
            /* bit = binary AND of ch value and bitmask 10000000 */
            /* only care about the value of the 7th bit */
            bit = ch & bitmask;
            ch = ch << 1;
            
            #ifdef DEBUG_DECOMPFILE
            printf("DEBUG: ch after ch << 1 = %d | bit = %d\n", ch, bit);
            #endif
            
            /* if the 7th bit was 0 - go left */
            if(bit == 0)
            {
                #ifdef DEBUG_DECOMPFILE
                printf("DEBUG: bit = 0 \033[0;33m GOING LEFT \033[0m --- Address of probe = %p\n", probe);
                #endif

                /* move the probe to the left child */
                probe = probe->left;
                /* character at probe */
                probeCh = probe->ch;

                #ifdef DEBUG_DECOMPFILE
                printf("DEBUG: probeCh = %d\n", probeCh);
                #endif

                /* if the child has a character, i.e. probeCh is NOT 
                equal to the flag value set before, print that character*/
                if(probeCh != -10)
                {
                    #ifdef DEBUG_DECOMPFILE
                    printf("DEBUG: \033[0;37mPRINTING ->left->ch = %c\033[0m\n", letters[probeCh]);
                    #endif
                    /* print in the character at that leaf */
                    fprintf(outputp, "%c", letters[probeCh]);
                    /* reset the probe to point to the root of the tree */
                probe = tree;
                }
            }

            /* if the 7th bit was 1 - go right*/
            /* same process */
            if(bit != 0)
            {
                #ifdef DEBUG_DECOMPFILE
                printf("DEBUG: bit = 1 \033[0;33m GOING RIGHT \033[0m Address of probe = %p\n", probe);
                #endif

                probe = probe->right;
                probeCh = probe->ch;

                #ifdef DEBUG_DECOMPFILE
                printf("DEBUG: probeCh = %d\n", probeCh);
                #endif
                
                if(probeCh != -10)
                {
                    #ifdef DEBUG_DECOMPFILE
                    printf("DEBUG: \033[0;33mPRINTING ->right->ch = %c\033[0m\n", letters[probeCh]);
                    #endif

                    fprintf(outputp, "%c", letters[probeCh]);
                    probe = tree;
                }
            }
        }
    }
    fclose(inputp);
    fclose(outputp);
    
    printf("\033[1;30m<<< DECOMPRESSED SUCCESSFULLY >>>\033[0m\n");

    return;
}

/* because of the arithmetic nature of how the onetwocodes were written, we need
to mathematically reverse them to get huffman prefix property */
void reverseCodes(long onetwocodes[], long huffmanCodes[])
{
    /* explanation of process: https://medium.com/@ManBearPigCode/how-to-reverse-a-number-mathematically-97c556626ec6 */
    int index;
    int number, lastDigit;
    int reverse;
    for(index=0;index<NO_OF_CHARS;index++)
    {
        number = onetwocodes[index];
        reverse = 0;
        while(number>0)
        {
            lastDigit = number % 10;
            reverse = reverse*10 + lastDigit;
            number = number / 10;
        }
        huffmanCodes[index]=reverse;
    }
}

void printCodes(long huffmanCodes[], char letters[], int frequencies[])
{
    printf("\033[0;33m");
    int i;
    printf("TABLE OF CHARACTERS AND THEIR HUFFMAN CODES:\n");
    printf("+-----+------+-------+-------+----------------+\n");
    printf("| idx |  ch  | freq  | ASCII |      code      |\n");
    printf("+-----+------+-------+-------+----------------+\n");
    for(i=0;i<NO_OF_CHARS; i++)
    {
        printf("| %d", i);
        if(i<10) /* fix the spacing */
        {
            printf("   ");
        }
        if(i<100 && i>=10)
        {
            printf("  ");
        }

        /* print letters */
        if(letters[i]=='\n'){
            printf("| \\n   ");
        }
        else if(letters[i]=='\r'){
            printf("| \\r   ");
        }
        else{
            printf("| '%c'  ", letters[i]);
        }

        /* print frequencies */
        printf("|  %d  ", frequencies[i]); 
        if(frequencies[i]<10) /* fix the spacing */
        {
            printf("  ");
        }
        if(frequencies[i]<100 && frequencies[i]>=10)
        {
            printf(" ");
        }

        /* print ascii values */
        printf("|  %d  ", letters[i]);
        if(letters[i]<10) /* fix the spacing */
        {
            printf("  ");
        }
        if(letters[i]<100 && letters[i]>=10)
        {
            printf(" ");
        }


        printf("| %ld\n", huffmanCodes[i]);
    }
    printf("+-----+------+-------+-------+----------------+\n");
    printf("NOTE: These huffman codes are printed in a special (1,2) notation\n"
           "rather than a (1,0) notation due to the how the code works. Regardless\n"
           "the huffman codes still work as intended. To convert to (1,0) notation,\n"
           "1=0 and 2=1.\n");
    /*
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);  
    printf("ASCII value of %c = %d\n", c, c);
    */
    printf("\033[0m"); 
}

void COMPRESS(int state)
{
    node_t* tree;
    /* given an array of characters and their frequencies */
    char letters[NO_OF_CHARS]={'a', 'b', 'c', 'd', 'e', 'f', 'g',
                               'h', 'i', 'j', 'k', 'l', 'm', 'n',
                               'o', 'p', 'q', 'r', 's', 't', 'u',
                               'v', 'w', 'x', 'y', 'z', ' ', '\n', 
                               '\r', '0', '1', '2', '3', '4', '5', 
                               '6', '7', '8', '9', '-' ,'_', '|', 
                               ':', 'A', 'B', 'C', 'D', 'E', 'F', 
                               'G', 'H', 'I', 'J', 'K', 'L', 'M', 
                               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                               'U', 'V', 'W', 'X', 'Y', 'Z', '/', 
                               '.', ','};
    int frequencies[NO_OF_CHARS]={24, 15, 28, 43, 128, 23, 20, 61, 
                                  71, 21, 16, 40, 24, 69, 76, 20, 
                                  41, 51, 64, 91, 28, 10, 24, 18, 
                                  68, 14, 130, 50, 1, 10, 10, 10, 
                                  10, 10, 10, 10, 10, 10, 10, 60, 
                                  20, 10, 15, 81, 15, 28, 43, 128, 
                                  23, 20, 61, 71, 21, 16, 40, 24, 
                                  69, 76, 20, 41, 51, 64, 91, 28, 
                                  10, 24, 18, 15, 14, 9, 9, 9};
    long onetwocodes[NO_OF_CHARS];
    long huffmanCodes[NO_OF_CHARS];

    makeHuffmanTree(&tree, frequencies, NO_OF_CHARS);
    makeCodes(onetwocodes, tree, 0);
    reverseCodes(onetwocodes, huffmanCodes);

    /* define PRINT_CODES in the preprocessing directives if you want to 
    see a table output of the characters, their frequencies, ascii codes 
    and huffman codes */
    #ifdef PRINT_CODES
    printCodes(onetwocodes, letters,frequencies);
    #endif

    if(state==1)
    {
        compressFile(huffmanCodes, letters);
        return;
    }
    else if(state==0)
    {
        decompFile(tree, letters);
        return;
    }
}
