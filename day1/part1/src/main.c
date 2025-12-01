#include <stdio.h>
#include <string.h>

#define N_TICKS 100
#define START 50

int currentPos = START;

int rotate(char dir, int length);
int numberOfZeros = 0;

void main(void)
{
    FILE *file = fopen("test1.txt", "r");
    // FILE *file = fopen("input1.txt", "r");

    char dir;
    int length;
    
    printf("The dial starts by pointing at %d\n", START);
    while (fscanf(file, " %c%d", &dir, &length) == 2) {
        int ans = rotate(dir, length);
        printf("The dial is rotated %c%d to point at %d\n", dir, length, ans);
        if(ans == 0)
        {
            numberOfZeros++;
        }
    }
    fclose(file);

    printf("\nNumber of zeros = %d\n", numberOfZeros);
}

int rotate(char dir, int length)
{
    int ans = 0;
    if(dir == 'R')
    {
        ans = (currentPos + length);
    }
    else if (dir == 'L')
    {
        ans = (currentPos - length);
    }

    currentPos = (ans % N_TICKS + N_TICKS) % N_TICKS;
    return currentPos;

}


