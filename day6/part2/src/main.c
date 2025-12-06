#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LINE_LENGTH 5000
#define MAX_ROWS 10
#define LENGTH 256

int nRows = 0;
char delim = ' ';
long long ans = 0;
long long totalAns = 0;

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

    char *opLine = lines[nRows - 1];
    int colPos[LINE_LENGTH];
    int nCols = 0;
    printf("ops:\n%s\n", opLine);
    for (int i = 0; opLine[i] != '\0'; i++)
    {
        if (opLine[i] != ' ')
        {
            colPos[nCols++] = i;  // column starts here
            // find next non space char
            while(opLine[i] != ' ' && opLine[i] != '\0'){ i++; }
        }
    }

    for (int c = 0; c < nCols; c++)
    {
        char op = opLine[colPos[c]]; // operator

        printf("Column %d operator = %c\n", c, op);

        char nums[numericRows][LENGTH];

        for (int r = 0; r < nRows - 1; r++) // numeric rows
        {
            int start = colPos[c];
            int end = (c + 1 < nCols) ? colPos[c + 1] : strlen(lines[r]);

            int len = end - start;
            if (len >= LENGTH) len = LENGTH-1;
            
            strncpy(nums[r], &lines[r][start], len);
            nums[r][len] = '\0'; 

            printf("num = %s\n", nums[r]);
        }

        // Here we should have all numbers
        // nums
        // loop through first num
        char columnNumber[128];
        int pos = 0;
        long long columnNum = 0;
        for (int i = 0; nums[0][i] != '\0'; i++)
        {   
            for (int j = 0; j < nRows-1; j++)
            {
                printf("char %c\n", nums[j][i]);
                columnNumber[pos] = nums[j][i]; 
                pos ++;
            }

            columnNumber[pos] = '\0'; // NULL terminate
            pos = 0;
            columnNum = atoll(columnNumber);
            printf("%lld\n", columnNum);
            if(op == '*')
            {
                if(ans == 0)
                {
                    ans = columnNum;
                }
                else if (columnNum != 0)
                {
                    ans *= columnNum;
                }
            }
            else if(op == '+')
            {
                ans += columnNum;
            }
        }
        printf("ans = %lld\n", ans);
        totalAns += ans;
        ans = 0;
        printf("\n");
    }
    printf("totalAns = %lld\n", totalAns);
}

