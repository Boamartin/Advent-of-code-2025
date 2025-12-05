#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    long long start;
    long long end;
} range_t;

#define MAX_RANGES 1000
#define MAX_NUMS   1000

bool numberInRange(long long number, range_t* range);
bool isFresh(long long number, range_t *ranges, int nRanges);

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");

    char line[256];

    range_t ranges[MAX_RANGES];
    long long     values[MAX_NUMS];

    int nRanges = 0;
    long long nValues = 0;
    long long ans = 0;

    bool readingRanges = true;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        // blank line found
        if (line[0] == '\0') {
            readingRanges = false;
            continue;
        }

        if (readingRanges) {
            long long a, b;
            if (sscanf(line, "%lld-%lld", &a, &b) == 2) {
                ranges[nRanges].start = a;
                ranges[nRanges].end   = b;
                nRanges++;
            }
        } else {
            long long x;
            if (sscanf(line, "%lld", &x) == 1) {
                values[nValues++] = x;
            }
        }
    }

    fclose(file);

    printf("Ranges:\n");
    for (int i = 0; i < nRanges; i++)
    {
        printf("  %lld - %lld\n", ranges[i].start, ranges[i].end);
    }

    printf("\nValues:\n");
    for (int i = 0; i < nValues; i++)
    {
        printf("  %lld", values[i]);
        if(isFresh(values[i], ranges, nRanges))
        {
            printf(" Fresh");
            ans ++;
        }
        printf("\n");
    }

    printf("ans = %lld\n", ans);
}

bool isFresh(long long number, range_t *ranges, int nRanges)
{
    for (int i = 0; i < nRanges; i++)
    {
        if(numberInRange(number, &ranges[i]))
        {
            return true;
        }
    }
    return false;
}

bool numberInRange(long long number, range_t* range)
{
    if(number >= range->start && number <= range->end)
    {
        return true;
    }
    else
    {
        return false;
    }
}