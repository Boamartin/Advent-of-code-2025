#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_MAP_SIZE 200

typedef struct {
    char data[MAX_MAP_SIZE][MAX_MAP_SIZE];
    long long value[MAX_MAP_SIZE][MAX_MAP_SIZE];
    int rows;
    int cols;
} map_t;

long long nSplits = 0;

map_t map = {0};

void printMap(map_t* map);
void printValueMap(map_t* map);
char getChar(map_t* map, int row, int col);
void addPadding(map_t *map);
bool addTachyon(map_t* map, int row, int col);

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");
    
    // int ans = 0;
    char line[MAX_MAP_SIZE];

    while (map.rows < MAX_MAP_SIZE && fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        strncpy(map.data[map.rows], line, MAX_MAP_SIZE);
        map.data[map.rows][MAX_MAP_SIZE - 1] = '\0';
        map.cols = strlen(line);
        map.rows++;
    }
    fclose(file);

    addPadding(&map);
    printMap(&map);
    // printValueMap(map);

    for (int row = 1; row < map.rows-1; row++)
    {   
        for (int cols = 1; cols < map.cols-1; cols++)
        {
            if(addTachyon(&map, row, cols))
            {
                map.data[row][cols] = '|';
            }
            printf("%c", getChar(&map, row, cols));
        }
        printf(" Row %d\n", row);
    }
    printf("ans = %lld\n", nSplits);
    // sum up bottom row of value map
    
    printf("last row\n");
    long long ans = 0;
    for (int i = 1; i < map.cols-1; i++)
    {
        ans += map.value[map.rows-2][i];
        printf("%lld,", map.value[map.rows-2][i]);
    }
    printf("\nans = %lld\n", ans);
    
}

bool addTachyon(map_t* map, int row, int col)
{
    bool ans = false;
    // Check if ^ to the right and | above it or S above
    char top = getChar(map, row-1, col);
    char right = getChar(map, row, col+1);
    char left = getChar(map, row, col-1);
    char topRight = getChar(map, row-1, col+1);
    char topLeft = getChar(map, row-1, col-1);
    char below = getChar(map, row+1, col);
    char current = getChar(map, row, col);
    if(right == '^' && topRight == '|')
    {
        ans = true;
    }
    if(top == 'S')
    {
        map->value[row][col] = 1;
        ans = true;
    }
    if(current == '.' && top == '|')
    {
        ans = true;
    }
    if(left == '^' && topLeft == '|')
    {
        ans = true;
    }
    if(current == '^' && top == '|')
    {
        nSplits ++;
    }

    // Numbers
    if(top == 'S')
    {
        map->value[row][col] = 1;
    }
    if(current != '^' && map->value[row-1][col] != 0)
    {
        map->value[row][col] = map->value[row-1][col];
    }
    if(left == '^')
    {
        map->value[row][col] += map->value[row-1][col-1];
    }
    if(right == '^')
    {
        map->value[row][col] += map->value[row-1][col+1];
    }
    return ans;
}

void printMap(map_t* map)
{
    for (int i = 0; i < map->rows; i++) {
        printf("%s\n", map->data[i]);
    }
}

void printValueMap(map_t* map)
{
    for (int row = 1; row < map->rows-1; row++)
    {   
        for (int cols = 1; cols < map->cols-1; cols++)
        {
            printf("%d,", map->value[row][cols]);
        }
        printf("\n");
    }
}

char getChar(map_t* map, int row, int col)
{
    return map->data[row][col];
}

void addPadding(map_t *map)
{
    int r, c;
    char pad = '#';

    // Shift down and right by 1
    for (r = map->rows - 1; r >= 0; r--) {
        for (c = map->cols - 1; c >= 0; c--) {
            map->data[r + 1][c + 1] = map->data[r][c];
        }
    }

    // Top border
    for (c = 0; c < map->cols + 2; c++)
        map->data[0][c] = pad;

    // Bottom border
    for (c = 0; c < map->cols + 2; c++)
        map->data[map->rows + 1][c] = pad;

    // Left + right borders
    for (r = 1; r < map->rows + 1; r++) {
        map->data[r][0] = pad;
        map->data[r][map->cols + 1] = pad;
        map->data[r][map->cols + 2] = '\0';
    }

    map->rows += 2;
    map->cols += 2;
}