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

map_t map = {0};

void printMap(map_t map);
char getChar(map_t map, int row, int col);

void main(void)
{
    FILE *file = fopen("input/test1.txt", "r");
    // FILE *file = fopen("input/input1.txt", "r");
    
    char line[MAX_MAP_SIZE];

    while (map.rows < MAX_MAP_SIZE && fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        strncpy(map.data[map.rows], line, MAX_MAP_SIZE);
        map.data[map.rows][MAX_MAP_SIZE - 1] = '\0';
        map.cols = strlen(line);
        map.rows++;
    }

    fclose(file);

    printMap(map);

    // Loop through map and check all eight neighbours
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

