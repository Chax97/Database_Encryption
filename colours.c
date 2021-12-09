#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG
/*
#define FUN */

int main(void)
{
    #ifdef FUN
    char lmao[123];
    #endif
    printf("\033[0;33m");
    printf("Hello world\n");
    #ifdef FUN
    scanf("%s", lmao);
    #endif
    printf("\033[0m");
    printf("test text\n");

    printf("\033[0;30mthis is dark green\n\033[0m");
    printf("\033[0;31mthis is red\n\033[0m");
    printf("\033[0;32mthis is green\n\033[0m");
    printf("\033[0;33mthis is yellow\n\033[0m");
    printf("\033[0;34mthis is blue\n\033[0m");
    printf("\033[0;35mthis is magenta\n\033[0m");
    printf("\033[0;36mthis is cyan\n\033[0m");     
    printf("\033[0;37mthis is white\n\033[0m");

    printf("\033[1;30mthis is bold light blue?\n\033[0m");
    printf("\033[1;31mthis is bold red\n\033[0m");
    printf("\033[1;32mthis is bold green\n\033[0m");
    printf("\033[1;33m this is bold yellow\n\033[0m");
    printf("\033[1;34mthis is bold blue\n\033[0m");
    printf("\033[1;35mthis is bold magenta\n\033[0m");
    printf("\033[1;36mthis is bold cyan\n\033[0m");
    printf("\033[1;37mthis is bold white\n\033[0m");


    printf("\033[1;36m");
    /* bold cyan text */
    printf("\n\033[0m");


    return 0;
}
