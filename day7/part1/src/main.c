#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_MAP_SIZE 500

typedef struct {
    char data[MAX_MAP_SIZE][MAX_MAP_SIZE];
    int rows;
    int cols;
} map_t;

long long nSplits = 0;

int dRow[8] = {-1, -1, -1, 0, 1, 1,  1,  0};
int dCol[8] = {-1,  0,  1, 1, 1, 0, -1, -1};

map_t map = {0};

void printMap(map_t map);
char getChar(map_t map, int row, int col);
void setChar(map_t map, int row, int col, char data);
void addPadding(map_t *map);
int getNeighbours(map_t* map, int row, int col);
bool addTachyon(map_t* map, int row, int col);

void main(void)
{
    // FILE *file = fopen("input/test1.txt", "r");
    FILE *file = fopen("input/input1.txt", "r");
    
    int ans = 0;
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
    printMap(map);

    for (int row = 1; row < map.rows-1; row++)
    {   
        for (int cols = 1; cols < map.cols-1; cols++)
        {
            if(addTachyon(&map, row, cols))
            {
                map.data[row][cols] = '|';
            }
            printf("%c", getChar(map, row, cols));
        }
        printf(" Row %d\n", row);
    }
    printf("ans = %lld\n", nSplits);
}

bool addTachyon(map_t* map, int row, int col)
{
    // Check if ^ to the right and | above it or S above
    char top = getChar(*map, row-1, col);
    char right = getChar(*map, row, col+1);
    char left = getChar(*map, row, col-1);
    char topRight = getChar(*map, row-1, col+1);
    char topLeft = getChar(*map, row-1, col-1);
    char current = getChar(*map, row, col);
    if(right == '^' && topRight == '|')
    {
        return true;
    }
    if(top == 'S')
    {
        return true;
    }
    if(current == '.' && top == '|')
    {
        return true;
    }
    if(left == '^' && topLeft == '|')
    {
        return true;
    }
    if(current == '^' && top == '|')
    {
        nSplits ++;
    }
    return false;
}

void printMap(map_t map)
{
    for (int i = 0; i < map.rows; i++) {
        printf("%s\n", map.data[i]);
    }
}

char getChar(map_t map, int row, int col)
{
    return map.data[row][col];
}

void setChar(map_t map, int row, int col, char data)
{
    map.data[row][col] = data;
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

int getNeighbours(map_t* map, int row, int col)
{
    int ans = 0;
    char currentChar;
    for (int i = 0; i < 8; i++)
    {
        currentChar = getChar(*map, row + dRow[i], col + dCol[i]);
        // printf("current char = %c\n", currentChar);
        if(currentChar == '@')
        { 
            ans++; 
        }
    }
    return ans;
}