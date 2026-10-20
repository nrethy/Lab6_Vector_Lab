/*
 * Filename: main.c
 * Author: Noah Rethwisch
 * Created: 9/29/2026
 * Descripton: main method for the vector calculator
 */

#include <stdio.h>
#include <string.h>
#include "newlogic.h"

int main(int argc, char *argv[]) {
    char data[20];
    if (argc > 1 && strcmp(argv[1], "-h") == 0){
        printf(" a = 1 2 3 define a vector\n");
        printf(" a = c + b add subtract or multiply, and output to vector\n");
        printf(" a + 2 do an operation and output to nothing\n");
        printf(" a print vector\n");
        printf(" list lists every vector\n");
        printf(" clear clears all vectors\n");
        printf(" quit exits\n");
        return 0;
    }
    while (1) {
        printf("minimat> ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0'; 
        if (strcmp(data, "quit") == 0) {
            return 0;
        }
        logic(data);
        memset(data, 0, sizeof(data));
    }
    return 0;
}
