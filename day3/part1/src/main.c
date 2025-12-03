#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 1024
#define CHAR_TO_INT 48


char getNthLetter(char* text, int index);
int getMaxJoltage(char* bank);

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
        // For 2 batteries sort out the largest number which has atleast (2-1) numbers to its left
        // Loop left to right keep track of largest number which has a position > 1
        // Then loop between 1 and the position of the previous number and search for the largest number in that range (same loop?)
    }
    fclose(file);
    printf("ans = %lld", ans);
}

char getNthLetter(char* text, int index)
{
    return text[index];
}

int getMaxJoltage(char* bank)
{
    int bankLength = strlen(bank);
    printf("%s\n", bank);
    
    // find left most battery
    int firstBattery = 0;
    int firstBatteryIndex = 0;
    int secondBattery = 0;
    int largest = 0;
    int current = 0;
    //                              v = 1 here to keep atleast one digit to the left
    for (int i = (bankLength - 1) - 1; i >= 0; i--)
    {
        current = (int)getNthLetter(bank, i) - CHAR_TO_INT;
        if(current >= largest)
        {
            largest = current;
            firstBatteryIndex = i;
        }
        // printf("%c ", getNthLetter(bank, i));
    }
    firstBattery = largest;
    // printf("the first battery is %d\n", firstBattery);
    
    // find right most battery
    largest = 0;
    current = 0;
    for (int i = (bankLength - 1) - 0; i >= firstBatteryIndex + 1; i--)
    {
        current = (int)getNthLetter(bank, i) - CHAR_TO_INT;
        if(current > largest)
        {
            largest = current;
        }
        // printf("%c ", getNthLetter(bank, i));
    }
    secondBattery = largest;
    // printf("\n");
    // printf("the second battery is %d\n", secondBattery);

    printf("%d%d\n", firstBattery, secondBattery);

    return firstBattery*10 + secondBattery;
}

