/*
#define DEBUG_COMPRESSION
#define DEBUG_COMPRESSFILE
#define PRINT_CODES 
#define DEBUG_DECOMPFILE 
*/

#define NO_OF_CHARS 73
#define INPUT_FILE_NAME "A_DB_STORAGE.txt"
#define OUTPUT_FILE_NAME "A_DB_STORAGE_COMP.bin"
#define DECOMP_FILE_NAME "A_DB_STORAGE_DECOMP.txt"
/*
#define DECOMP_FILE_NAME "A_DB_STORAGE.txt"
*/
/* define a node structure */
struct node{
    int ch; /* int = index of ch in letter array */
    int freq; /* frequency of character */
    /* pointers to left and right children */
    struct node *left;
    struct node *right;
};
typedef struct node node_t;

int getSmaller(node_t* nodearray[], int indexcmp);
void makeHuffmanTree(node_t** tree, int freq[], int arSz);
void makeCodes(long onetwocodes[], node_t *nodeprobe, long code);
void compressFile(long huffmanCodes[], char letters[]);
void decompFile(node_t* tree, char letters[]);
void reverseCodes(long onetwocodes[], long huffmanCodes[]);
void printCodes(long huffmanCodes[], char letters[], int frequencies[]);
void COMPRESS(int state);
