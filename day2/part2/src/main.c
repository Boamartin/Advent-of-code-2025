#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void isValidId(long long id);
bool equalParts(long long id, int nDigits, int divisor);

#define LINE_LENGTH 512
long long ans = 0;

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");

    
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
                isValidId(id);
            }
            

            id_str = strtok_r(NULL, ",", &save_comma);
        }
    }
    fclose(file);
    printf("Adding up all the invalid IDs in this example produces %lld.", ans);
}


void isValidId(long long id)
{
    int nDigits = (int)floor(log10(id)) + 1;

    int divisor = 2;
    while (divisor <= nDigits)
    {
        if(nDigits % divisor == 0)
        {
            if(equalParts(id, nDigits, divisor))
            {
                // printf("%lld\n", id);
                ans += id;
                break;
            }
        }
        divisor++;
    }
}

bool equalParts(long long id, int nDigits, int divisor)
{
    char id_str[200];
    sprintf(id_str, "%lld", id);

    int partLen = nDigits / divisor;

    char part[128];
    part[partLen] = '\0';

    // Extract first part
    memcpy(part, id_str, partLen);
    int first = atoi(part);

    for (int p = 1; p < divisor; p++) 
    {
        // Extract the following parts
        memcpy(part, id_str + p * partLen, partLen);
        part[partLen] = '\0';

        int next = atoi(part);

        if (next != first){ return false; }
    }

    return true;
}