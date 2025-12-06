#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 5000
#define MAX_ROWS 10
int nRows = 0;
char delim = ' ';

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");

    char lines[MAX_ROWS][LINE_LENGTH];

    printf("Input:\n");
    while (fgets(lines[nRows], LINE_LENGTH, file)) 
    {
        lines[nRows][strcspn(lines[nRows], "\n")] = 0;
        printf("%s\n", lines[nRows]);
        nRows++;
    }
    // nRows --;
    int numericRows = nRows - 1;
    int operatorRow = numericRows;
    printf("\n");
    fclose(file);

    char *saveptr[nRows]; // Used for strtok_r
    for (size_t i = 0; i < nRows; i++)
    {
        saveptr[i] = NULL;
    }
    
    // first strtok_r
    char* num;
    char* operator;
    long long number;
    long long ans = 0;
    long long TotalAns = 0;

    while(true)
    {
        ans = 0;
        operator = strtok_r(saveptr[operatorRow] == NULL ? lines[operatorRow] : NULL,
                            &delim,
                            &saveptr[operatorRow]);
        if(operator == NULL){ break; }
        // printf("opperator = %s\n", operator);
        
        for (size_t i = 0; i < numericRows; i++)
        {
            num = strtok_r(saveptr[i] == NULL ? lines[i]: NULL,
                           &delim,
                           &saveptr[i]);
            number = atoll(num);
            // printf("num = %lld", number);
            if(operator[0] == '*')
            {
                // printf(" MUL\n");
                if(ans != 0){ ans *= number; }
                else        { ans  = number; } 
            }
            else if(operator[0] == '+')
            {
                // printf(" PLUS\n");
                ans += number;
            }
        }
        printf("ans = %lld\n", ans);
        TotalAns += ans;
    }

    printf("Total ans = %lld\n", TotalAns);
}

