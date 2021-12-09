#define DB_READ "A_DB_DISPLAY.txt"
#define DB_LOAD "A_DB_STORAGE.txt"

#define PRINT_LINE_LEN 80
/*
#define DEBUG_LOADING
*/
void print_DB (const criminal_t criminals[], int arrSize, int crimCount);
void save_DB (const criminal_t criminals[], int arrSize, int crimCount);
void endBuff(char buffer[], char outputS[]);
int load_DB (criminal_t criminals[], int arrSize);


