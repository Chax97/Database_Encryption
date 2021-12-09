/*#include <stdio.h>
int intOrChar(float input);

int main (void)
{
    float input;
    int ret;
    printf("\nInsert day\n");
    scanf("\n %f",&input);
    ret=intOrChar(input);
    if(ret==1)
    {
        printf("\nNOT INTEGER\n\n");
    }
    else {
        printf("\nINTEGER\n\n");
    }

    return 0;
}

int intOrChar(float input)
{
    int status;
    int test;
    test=(int)input;
    ++test;
    if((test-input)!=1)
    {
        status=1;
    }
    else
    {
        status=0;
    }
    return status;
}
*/


#include <stdio.h>
int main (void)
{
    char huh[1000];
    printf("Enter string > ");
    scanf("%[^\n]", huh);
    printf("Entered string: %s\n", huh);
    return 0;
}
