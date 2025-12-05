#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    long long start;
    long long end;
} range_t;

typedef struct {
    long long value;
    bool startOfRange;
} rangeElement_t;

#define MAX_RANGES 1000
#define MAX_NUMS   1000

void sortRanges(rangeElement_t *rangeElements, int nRangeElements);
int compareRangeElements(const void *a, const void *b);

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");

    char line[256];

    range_t ranges[MAX_RANGES];
    rangeElement_t rangeElements[MAX_RANGES];
    long long     values[MAX_NUMS];

    int nRanges = 0;
    int nRangeElements = 0;
    long long nValues = 0;
    long long ans = 0;

    bool readingRanges = true;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        // blank line found
        if (line[0] == '\0') 
        {
            readingRanges = false;
            continue;
        }

        if (readingRanges) 
        {
            long long a, b;
            if (sscanf(line, "%lld-%lld", &a, &b) == 2) {
                ranges[nRanges].start = a;
                ranges[nRanges].end   = b;
                nRanges++;

                rangeElements[nRangeElements].value = a;
                rangeElements[nRangeElements].startOfRange = true;
                nRangeElements++;
                rangeElements[nRangeElements].value = b;
                rangeElements[nRangeElements].startOfRange = false;
                nRangeElements++;
            }
        }
    }
    fclose(file);
    
    // Sort rangeElements based on value
    sortRanges(rangeElements, nRangeElements);

    long long startOfRange = 0;
    long long endOfRange = 0;
    int delta = 0;
    bool newrange = true;
    for (int i = 0; i < nRangeElements; i++)
    {
        if(rangeElements[i].startOfRange){ delta ++; }
        else                             { delta --; }
        if(newrange)
        {
            // start of range
            startOfRange = rangeElements[i].value;
        }
        if(delta == 0)
        {
            // end of range
            endOfRange = rangeElements[i].value;
            ans += endOfRange - startOfRange + 1;
            newrange = true;
        }
        else
        {
            newrange = false;
        }
    }
    printf("ans = %lld\n", ans);
}

void sortRanges(rangeElement_t *rangeElements, int nRangeElements)
{
    qsort(rangeElements, nRangeElements, sizeof(rangeElement_t), compareRangeElements);

}

int compareRangeElements(const void *a, const void *b)
{
    const rangeElement_t *ra = a;
    const rangeElement_t *rb = b;

    if (ra->value < rb->value) return -1;
    if (ra->value > rb->value) return 1;

    if (ra->startOfRange == rb->startOfRange) return 0;
    return ra->startOfRange ? -1 : 1;
}