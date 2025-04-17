#include "source.h"

typedef struct {
    char program[50];
    char author[50];
    char helper[50];
    char date[15];
    char version[15];
} Claim;
Claim claim;

void saveClaim() {
    FILE* file = fopen("../claim.clm", "w+");  // Mode écriture
    if (file == NULL) {
        printf_d("Error: unable to open claim file for writing.\n");
        return;
    }

    fprintf(file, "@Program: %s\n", claim.program);
    fprintf(file, "@author: %s\n", claim.author);
    fprintf(file, "@help: %s\n", claim.helper);
    fprintf(file, "@date: %s\n", claim.date);
    fprintf(file, "@version: %s\n\n", claim.version);

    fclose(file);
}

void loadClaim() {
    FILE* file = fopen("../claim.clm", "r");  // Mode lecture
    if (file == NULL) {
        printf_d("Error: unable to open claim file for reading.\n");
        return;
    }

    char line[100];
    printf("/******************************\n");
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "@Program:", 9) == 0) {
            sscanf(line, "@Program: %s", claim.program);
            printf("@Program: %s\n", claim.program);
        }
        else if (strncmp(line, "@author:", 8) == 0) {
            sscanf(line, "@author: %s", claim.author);
            printf("@author: %s\n", claim.author);
        }
        else if (strncmp(line, "@help:", 6) == 0) {
            sscanf(line, "@help: %s", claim.helper);
            printf("@help: %s\n", claim.helper);
        }
        else if (strncmp(line, "@date:", 6) == 0) {
            sscanf(line, "@date: %s", claim.date);
            printf("@date: %s\n", claim.date);
        }
        else if (strncmp(line, "@version:", 9) == 0) {
            sscanf(line, "@version: %s", claim.version);
            printf("@version: %s\n", claim.version);
        }
    }
    printf("******************************/\n");

    fclose(file);
}