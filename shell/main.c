#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <string.h>
#include <sys/types.h>
#include<unistd.h>

int main()
{


    char comm[100];

    do
    {
        printf("shell$>");
        gets(comm);
            system(comm);

    }
    while(strcmp(comm,"exit"));
   exit(0);
}
