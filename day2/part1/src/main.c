#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

bool isValidId(long long id);
#define LINE_LENGTH 512

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");

    long long ans = 0;
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char lineCopy[LINE_LENGTH];
        strcpy(lineCopy, line);

        // range
        char *save_comma;
        char *id_str = strtok_r(lineCopy, ",", &save_comma);
        while (id_str != NULL) {

            char rangeCopy[LINE_LENGTH];
            strcpy(rangeCopy, id_str);
            
            // printf("Range: '%s'\n", id_str);
            
            // IDs
            char *save_dash;
            char *token = strtok_r(rangeCopy, "-", &save_dash);

            long long rangeLow  = strtoll(token, NULL, 10);
            long long rangeHigh = strtoll(strtok_r(NULL, "-", &save_dash), NULL, 10);

            for (long long id = rangeLow; id <= rangeHigh; id++)
            {
                // check if the id is invalid
                if(!isValidId(id)){ 
                    ans += id;
                }
            }
            

            id_str = strtok_r(NULL, ",", &save_comma);
        }
    }
    fclose(file);
    printf("Adding up all the invalid IDs in this example produces %lld.", ans);
}


bool isValidId(long long id)
{
    int nDigits = (int)floor(log10(id)) + 1;

    if(nDigits % 2 != 0){ return true; } // if uneaven amount of digits two repeating answers are impossible
    
    char id_str[200];
    char firstHalf_str[100];
    char secondHalf_str[100];
    int  firstHalf;
    int  secondHalf;    

    sprintf(id_str,"%lld", id);
    strncpy(firstHalf_str, id_str, nDigits/2);
    strncpy(secondHalf_str, id_str + nDigits/2 ,nDigits/2);

    // null terminate
    firstHalf_str[nDigits/2] = '\0';
    secondHalf_str[nDigits/2] = '\0';

    firstHalf = atoi(firstHalf_str);
    secondHalf = atoi(secondHalf_str);

    if(firstHalf == secondHalf)
    {
        return false;
    }

    return true;
}