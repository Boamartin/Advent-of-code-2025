#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 1024

int getMaxJoltage(char* bank);

void main(void)
{
    FILE *file = fopen("input/test1.txt", "r");
    // FILE *file = fopen("input/input1.txt", "r");
    
    long long ans = 0;
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char lineCopy[LINE_LENGTH];
        strcpy(lineCopy, line);

        printf("%s\n", lineCopy);
        // For 2 batteries sort out the largest number which has atleast (2-1) numbers to its left
        // Loop left to right keep track of largest number which has a position > 1
        // Then loop between 1 and the position of the previous number and search for the largest number in that range (same loop?)
    }
    fclose(file);
}

int getMaxJoltage(char* bank)
{
    return 0;
}