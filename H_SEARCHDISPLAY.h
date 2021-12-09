#define DB_READ "A_DB_DISPLAY.txt"
#define DB_LOAD "A_DB_STORAGE.txt"

void printCrimlist(criminal_t criminals[], int crimCount);
int searchName(criminal_t criminals [], int crimCount, int matchedNames[]);
void printCriminal(criminal_t criminals[], int crimArrSize, int matchedNames[], int matchArrSize);
void printMatchedIDs(int matchArray[], int matchArrSz);
