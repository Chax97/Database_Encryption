int* convertCharToBit(int filesize, char* image_array_p);
void encryption(int filesize,int dataoffset,char* image_array_p, FILE* encrypted_image, FILE* cipher);
void decryption(char* image_array_p,int crimID,int dataoffset, int filesize,FILE* new_image);
void createKeys(int sub48keys[16][48]);


/*#define DEBUG_CREATE_KEYS*/
/*#define DEBUG_DECRYPT*/
/*#define DEBUG_ENCRYPT*/

