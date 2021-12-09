#define MAX_NAME_LEN 24
#define MAX_NUM_OF_CRIMINALS 50
#define MAX_STREET_LEN 30
#define MAX_SUBURB_LEN 50
#define MAX_STATE_LEN 50
#define MAX_OCCUP_LEN 30
#define MAX_FEATURES_LEN 100
#define MAX_CHARGE_LEN 100
#define MAX_DESCRIP_LEN 1000
#define MAX_STATEMENT_LEN 50
#define MAX_MOTIVE_LEN 30
#define MAX_STATUS_LEN 20
#define MAX_OFFENSES_COMMITTED 100

#define DEBUG


struct date{                    /*date struct*/
    int day;
    int month;
    int year;
};
typedef struct date date_t;

struct address{                         /*address struct*/
    int streetNumber;
    char streetName[MAX_STREET_LEN];
    char suburb[MAX_SUBURB_LEN];
    char state[MAX_STATE_LEN];
};
typedef struct address address_t;

struct offense{                         /*Offence records struct*/
    char charge[MAX_CHARGE_LEN];/* rm */
    date_t occurrence; 
    address_t crimLocation;
    char officer[MAX_NAME_LEN];/* rm */
    char descrip[MAX_DESCRIP_LEN];
    char offStatement[MAX_STATEMENT_LEN];/* rm */
    char victStatement[MAX_STATEMENT_LEN];/* rm */
    char witnStatement[MAX_STATEMENT_LEN];/* rm */
    char whoInvolved[MAX_NAME_LEN];/* rm */
};
typedef struct offense offense_t;

struct physical{                         /*physical characteristics struct*/
    char sex;
    double height;
    char features[MAX_FEATURES_LEN];     /*tatoos/gang affiliations...*/
};
typedef struct physical physical_t;

struct criminal{                         /*criminal information struct*/
    char lastName[MAX_NAME_LEN];
    char firstName[MAX_NAME_LEN];
    char currentStatus[MAX_STATUS_LEN];
    date_t dob; /*date of birth*/
    int numCharges;
    offense_t crimHistory[MAX_OFFENSES_COMMITTED];
    char occupation[MAX_OCCUP_LEN];
    address_t resAddress;
    physical_t physique;
};
typedef struct criminal criminal_t;

