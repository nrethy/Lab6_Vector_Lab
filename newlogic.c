/*
** Filename: newlogic.c
** Author: Noah Rethwisch
** Created: 10/14/2026
* Description: handles our parsing logic
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

int contains_logic(char identifier, struct Vector** array, int* length, int create){
    for(int i=3; i<(*length+3); i++){
        if((*array)[i].identifier == identifier){
            return i;
        }
    }
    if (!create || *length >= 55) {
        return -1;
    }
    struct Vector* temp = realloc(*array, (*length+4) * sizeof(struct Vector));
    if(array == NULL){
        printf("memory allocation failure\n");
        return -1;
    }
    *array = temp;
    (*array)[*length+3].identifier = identifier;
    return 3 + (*length)++;
};

char* logic(char data[]){
    double ijk[3];
    // 0, 1 and 2 are reserved for temporary vectors for scalars and outputs
    static struct Vector *vectors = NULL;
    if(vectors == NULL){
        vectors = malloc(3 * sizeof(struct Vector));
        if(vectors == NULL){
            printf("memory allocation failed\n");
            return 0;
        }
    }
    char test[50];
    struct Vector* output_vector;
    char dest, operator, a[5], b[5];
    int new_index, index_a, index_b;
    static int vector_count = 0;
    // check for empty data
    if(strcmp(data, "\0") == 0){
        return 0;
    // check for form a = 1 2 3
    }else if (sscanf(data, " %c = %lf %lf %lf", &dest, &ijk[0], &ijk[1], &ijk[2]) == 4) {
        new_index = contains_logic(dest, &vectors, &vector_count, 1);
        if(new_index == -1){
            printf("out of vectors\n");
            return 0;
        }
        set_vector(&vectors[new_index], ijk[0], ijk[1], ijk[2]);
        return 0;
    // check for form c = a + b
    }else if (sscanf(data, " %c = %s %c %s", &dest, a, &operator, b) == 4) {
        double b_value, a_value;
        new_index = contains_logic(dest, &vectors, &vector_count, 1);
        if(new_index == -1){
            printf("out of vectors\n");
            return 0;
        }
        output_vector = &vectors[new_index];
        if (sscanf(a, "%lf", &a_value) == 1) {
            index_a = 0;
            set_vector(&vectors[0], a_value, a_value, a_value); 
        }else{
            index_a = contains_logic(a[0], &vectors, &vector_count, 0);
            if(index_a == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
        if (sscanf(b, "%lf", &b_value) == 1) {
            index_b = 0;
            set_vector(&vectors[0], b_value, b_value, b_value); 
        }else{
            index_b = contains_logic(b[0], &vectors, &vector_count, 0);
            if(index_b == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
    // loading a file
    }else if (sscanf(data, "load <%49[^>]>", test) == 1){
        FILE *fp;
        char line[40];
        fp = fopen(test, "r");
        if(!fp){
            printf("Error opening file\n");
            return 0;
        }
        while(fgets(line,sizeof(line),fp)){
            if(sscanf(line, " %c,%lf,%lf,%lf", &dest, &ijk[0], &ijk[1], &ijk[2]) == 4) {
                new_index = contains_logic(dest, &vectors, &vector_count, 1);
                if(new_index == -1){
                    printf("out of vectors\n");
                    fclose(fp);
                    return 0;
                }
                set_vector(&vectors[new_index], ijk[0], ijk[1], ijk[2]);
            }else{
                printf("invalid line, skipping\n");
            }
        }
        fclose(fp);
        return 0;
        // saving a file
    }else if (sscanf(data, "save <%49[^>]>", test) == 1){
        FILE *fp;
        fp = fopen(test, "w");
        if(!fp){
            printf("error writing to file\n");
            return 0;
        }
        for(int i=3; i<vector_count+3; i++){
            fprintf(fp, "%c,%lf,%lf,%lf\n", vectors[i].identifier, vectors[i].ijk[0], vectors[i].ijk[1], vectors[i].ijk[2]);
        }
        fclose(fp);
        return 0;
    // check for form a + b
    }else if (sscanf(data, " %s %c %s", a, &operator, b) == 3) {
        double b_value, a_value;
        output_vector = &vectors[2];
        if (sscanf(a, "%lf", &a_value) == 1) {
            index_a = 0;
            set_vector(&vectors[0], a_value, a_value, a_value); 
        }else{
            index_a = contains_logic(a[0], &vectors, &vector_count, 0);
            if(index_a == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
        if (sscanf(b, "%lf", &b_value) == 1) {
            index_b = 1;
            set_vector(&vectors[1], b_value, b_value, b_value); 
        }else{
            index_b = contains_logic(b[0], &vectors, &vector_count, 0);
            if(index_b == -1){
                printf("invalid vector\n");
                return 0;
            }
        } 
    }else if(strcmp(data, "quit") == 0){
        static char test = 'a';
        free(vectors);
        return &test;
    // check for list
    }else if(strcmp(data, "list") == 0){
        for(int i=3; i<vector_count+3; i++){
            print(&vectors[i]);
        }
        return 0;
    // check for clear
    }else if(strcmp(data, "clear") == 0){
        free(vectors);
        vectors = malloc(3 * sizeof(struct Vector));
        vector_count = 0;
        return 0;
    // check for data by char
    }else if (sscanf(data, "%c", a) == 1){
        new_index = contains_logic(a[0], &vectors, &vector_count, 0);
        if(new_index != -1){
            print(&vectors[new_index]);
        }else{
            printf("invalid vector\n");
        }
        return 0;
    // invalid input
    }else {
        printf("invalid input\n");
    }
    // execute operations
    switch(operator){
        case '+':
            add(output_vector, &vectors[index_a], &vectors[index_b]);
            break;
        case '-':
            sub(output_vector, &vectors[index_a], &vectors[index_b]);
            break;
        case '*':
            mul(output_vector, &vectors[index_a], &vectors[index_b]);
            break;
        default:
            printf("invalid input\n");
            break;
    }
    print(output_vector);
    return 0;
}
