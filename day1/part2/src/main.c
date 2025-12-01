#include <stdio.h>
#include <string.h>

#define N_TICKS 100
#define START 50

int currentPos = START;


int numberOfZeros = 0;

typedef struct
{
    int nZeros;
    int newPos;
}rotation_t;

rotation_t rotate(char dir, int length); 


void main(void)
{
    // FILE *file = fopen("test1.txt", "r");
    FILE *file = fopen("input2.txt", "r");

    char dir;
    int length;
    
    printf("The dial starts by pointing at %d\n", START);
    while (fscanf(file, " %c%d", &dir, &length) == 2) {

        rotation_t rot = rotate(dir, length);
        printf("The dial is rotated %c%d to point at %d ", dir, length, rot.newPos);

        if(rot.nZeros)
        {
            printf("during this rotation, it points at 0 %d times", rot.nZeros);
        }
        
        printf("\n");
        
        numberOfZeros += rot.nZeros;
    }
    fclose(file);

    printf("\nNumber of zeros = %d\n", numberOfZeros);
}

rotation_t rotate(char dir, int length)
{
    rotation_t rot;
    rot.nZeros = 0;

    int start = currentPos;
    int delta = (dir == 'R') ? 1 : -1;

    for(int i = 0; i < length; i++)
    {
        start += delta;

        if(start >= N_TICKS) start -= N_TICKS;
        if(start < 0) start += N_TICKS;

        if(start == 0)
            rot.nZeros++;
    }

    currentPos = start;
    rot.newPos = currentPos;

    return rot;
}




