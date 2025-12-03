#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 1024
#define CHAR_TO_INT 48


char getNthLetter(char* text, int index);
long long getMaxJoltage(char* bank);

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");
    
    long long ans = 0;
    
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char bank[LINE_LENGTH];
        strcpy(bank, line);
        ans += getMaxJoltage((char *)bank);
    }
    fclose(file);
    printf("Total output joltage = %lld", ans);
}

char getNthLetter(char* text, int index)
{
    return text[index];
}

long long getMaxJoltage(char* bank)
{
    long long ans = 0;
    int bankLength = strlen(bank);
    // printf("%s\n", bank);

    int numberOfBatteriesToChoose = 12;

    int ithBattery = 0;
    int ithBatteryIndex_tmp = 0;
    int ithBatteryIndex = 0;
    int largest = 0;
    int current = 0;
    for (size_t i = 0; i < numberOfBatteriesToChoose; i++)
    {
        for (int j = (bankLength - numberOfBatteriesToChoose + i); j >= ithBatteryIndex; j--)
        {
            current = (int)getNthLetter(bank, j) - CHAR_TO_INT;
            if(current >= largest)
            {
                largest = current;
                ithBatteryIndex_tmp = j + 1;
            }
        }
        ithBattery = largest;
        ithBatteryIndex = ithBatteryIndex_tmp;
        largest = 0;
        current = 0;
        ans += (ithBattery * pow(10, numberOfBatteriesToChoose - i - 1));
    }
    return ans;
}

