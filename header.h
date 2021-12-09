/* the header file stores the function prototypes, structure definitions, and other predefined processes ONLY */
/* to compile a main.out file combining all individual .c files:

gcc -Wall -Werror -ansi -o main.out main.c shaman.c eric.c olivia.c faisal.c yongqi.c header.h

**************************************************************************/
/* #defines go here so many :[*/
#define MAX_NAME_LEN 24
#define MAX_NUM_OF_CRIMINALS 50
#define MAX_STREET_LEN 30
#define MAX_SUBURB_LEN 50
#define MAX_STATE_LEN 50
#define MAX_OCCUP_LEN 30
#define MAX_FEATURES_LEN 100
#define MAX_CHARGE_LEN 50
#define MAX_DESCRIP_LEN 50
#define MAX_STATEMENT_LEN 50
#define MAX_MOTIVE_LEN 30
#define MAX_STATUS_LEN 20
#define DB_READ "criminal_database_for_reading"
#define DB_LOAD "criminal_database_for_loading"

#define DEBUG

/* structure definitions go here */
typedef struct date{                    /*date struct*/
    int day;
    int month;
    int year;
}date_t;
/* typedef struct date date_t; */

struct address{                         /*address struct*/
    int streetNumber;
    char streetName[MAX_STREET_LEN];
    char suburb[MAX_SUBURB_LEN];
    char state[MAX_STATE_LEN];
};
typedef struct address address_t;

struct offense{                         /*Offense records struct*/
    char charge[MAX_CHARGE_LEN];
    date_t occurrence; 
    address_t crimLocation;
    char officer[MAX_NAME_LEN];
    char descrip[MAX_DESCRIP_LEN];
    char offStatement[MAX_STATEMENT_LEN];
    char victStatement[MAX_STATEMENT_LEN];
    char witnStatement[MAX_STATEMENT_LEN];
    char whoInvolved[MAX_NAME_LEN];
};
typedef struct offense offense_t;

struct physical{                         /*physical characteristics struct*/
    char sex;
    int height;
    char features[MAX_FEATURES_LEN];     /*tatoos/gang affiliations*/
};
typedef struct physical physical_t;

struct criminal{                         /*criminal information struct*/
    char lastName[MAX_NAME_LEN];
    char firstName[MAX_NAME_LEN];
    int crimID;
    char currentStatus[MAX_STATUS_LEN];
    date_t dob; /*date of birth*/
    offense_t crimHistory[100]; /*feature will - lists all offenses with this person */
    char occupation[MAX_OCCUP_LEN];
    address_t resAddress;
    physical_t physique;
};
typedef struct criminal criminal_t;

/* need to make */
int printSearchBy(void); /* shaman */
//void saveDB_READ (const criminal_t criminals[], int arrSize, int crimCount); /* shaman */
//void saveDB_LOAD (const criminal_t criminals[], int arrSize, int crimCount); /* shaman */
/* load to file function - shaman */
//int readDB_LOAD (criminal_t criminals[], int arrSize); /* shaman */
//void printMatchedIDs(int matchArray[], int matchArrSz); /*shaman*/
/* loading in an image - */

/* COMPLETE */
//void editCrim(criminal_t criminals[], int arrSize, int crimID); /* eric */
//void addCrim(criminal_t criminals[], int crimCount); /* faisal */
//void printAllCrims(criminal_t criminals[], int crimCount); /* yongqi */
//void printCriminal(criminal_t criminals[], int crimArrSize, int matchedNames[], int matchArrSize); /* olivia */
//int searchName(criminal_t criminals [], int crimCount, int matchedNames[]); /* faisal */ 
//void addCrim(criminal_t criminals[], int crimCount); /*faisal*/
//int ExCont(void); /* shaman */
//int escFunction (void); /* shaman */
//int skip(void); /*Eric*/
//int dateIsValid(criminal_t criminal) /*Eric*/


//long extract(FILE *image,long offset ,int size );
//unsigned long fsize(char* file);
//void image_to_bin( int crimCount);
//void bin_to_image(int crimID);
//int* convertCharToBit(int filesize, char* image_array_p);
//void encryption(char* binfile,char* image_array_p);
//void createKeys(int sub48keys[16][48]);

