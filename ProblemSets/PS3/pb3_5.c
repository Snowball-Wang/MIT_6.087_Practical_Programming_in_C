#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    char state_code_origin[8];
    char state_name[128];
    long int migration = 0;
    long int sum = 0;
    fp = fopen("stateoutflow0708.txt", "r");
    if(fp == NULL)
    {
        printf("Open file failure!");
        exit(-1);
    }

    printf("STATE\t\t\t\t\tTOTAL\n");
    printf("-----------------------------------------------\n");
    fscanf(fp, "%s %*s %*s %*s %*s %s %*d %*d %ld", state_code_origin, state_name, &migration);
    while(fscanf(fp, "%s %*s %*s %*s %*s %s %*d %*d %ld", state_code_origin, state_name, &migration)!=EOF)
    {
        if(strcmp(state_code_origin, "\"25\"") == 0)
        {
            printf("%-20s\t\t\t%-7ld\n", state_name, migration);
            sum += migration;
        }
    }
    printf("-----------------------------------------------\n");
    printf("Total\t\t\t\t\t%-7ld\n", sum);
    fclose(fp);
    return 0;
}
