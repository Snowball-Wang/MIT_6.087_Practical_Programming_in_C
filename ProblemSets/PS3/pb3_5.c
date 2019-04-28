#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define the wanted state code */
#define STATE_CODE "\"25\""
int main()
{
    FILE *fp;
	char title[1024];
    char state_code_origin[8];
    char state_name[128];
    long int aggr_agi = 0;
    long int sum = 0;
    fp = fopen("stateoutflow0708.txt", "r");
    if(fp == NULL)
    {
        printf("Open file failure!");
        exit(-1);
    }

    fscanf(fp, "%[^\n]", title); /* skip the first line of title */
    printf("%-20s\t\t\t%-7s\n", "STATE", "TOTAL");
    printf("-----------------------------------------------\n");
	/* traverse each line in text file and get aggr_agi number matching with the requirement */
    while(fscanf(fp, "%s %*s %*s %*s %*s %s %*d %*d %ld", state_code_origin, state_name, &aggr_agi)!=EOF)
    {
        if(strcmp(state_code_origin, STATE_CODE) == 0)
        {
            printf("%-20s\t\t\t%-7ld\n", state_name, aggr_agi);
            sum += aggr_agi;
        }
    }
    printf("-----------------------------------------------\n");
    printf("%-20s\t\t\t%-7ld\n", "Total", sum);
    fclose(fp);
    return 0;
}
