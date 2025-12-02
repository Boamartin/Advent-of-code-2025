#include <stdio.h>
#include <string.h>

void main(void)
{
    FILE *file = fopen("input/test1.txt", "r");
    // FILE *file = fopen("input/input1.txt", "r");

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        // IDs
        char *save_comma;
        char *id_str = strtok_r(line, ",", &save_comma);
        while (id_str != NULL) {
            printf("ID: '%s'\n", id_str);
            
            // Sub IDs
            char *save_dash;
            char *token = strtok_r(id_str, "-", &save_dash);
            while (token != NULL) {
                printf("\tSub IDs: %s\n", token);
                token = strtok_r(NULL, "-", &save_dash);
            }
            id_str = strtok_r(NULL, ",", &save_comma);
        }
    }
    fclose(file);
}