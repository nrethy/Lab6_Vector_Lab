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
int contains_logic(char identifier, struct Vector* array, int* length, int create){
    for(int i=0; i<*length; i++){
        if(array[i].identifier == identifier){
            return i;
        }
    }
    if (!create || *length >= 10) {
        return -1;
    }
    array[*length].identifier = identifier;
    return (*length)++;
};

char* logic(char data[]){
    double ijk[3];
    // 11, 12 and 13 are reserved for temporary vectors for scalars and outputs
    static struct Vector vectors[13];
    struct Vector* output_vector;
    char dest, operator, a[5], b[5];
    int new_index, index_a, index_b;
    static int vector_count = 0;
    // check for empty data
    if(strcmp(data, "\0") == 0){
        return 0;
    // check for form a = 1 2 3
    }else if (sscanf(data, " %c = %lf %lf %lf", &dest, &ijk[0], &ijk[1], &ijk[2]) == 4) {
        new_index = contains_logic(dest, vectors, &vector_count, 1);
        if(new_index == -1){
            printf("out of vectors\n");
            return 0;
        }
        set_vector(&vectors[new_index], ijk[0], ijk[1], ijk[2]);
        return 0;
    }
    // check for form c = a + b
    else if (sscanf(data, " %c = %s %c %s", &dest, a, &operator, b) == 4) {
        double b_value, a_value;
        new_index = contains_logic(dest, vectors, &vector_count, 1);
        if(new_index == -1){
            printf("out of vectors\n");
            return 0;
        }
        output_vector = &vectors[new_index];
        if (sscanf(a, "%lf", &a_value) == 1) {
            index_a = 11;
            set_vector(&vectors[11], a_value, a_value, a_value); 
        }else{
            index_a = contains_logic(a[0], vectors, &vector_count, 0);
            if(index_a == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
        if (sscanf(b, "%lf", &b_value) == 1) {
            index_b = 11;
            set_vector(&vectors[11], b_value, b_value, b_value); 
        }else{
            index_b = contains_logic(b[0], vectors, &vector_count, 0);
            if(index_b == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
    }
    // check for form a + b
    else if (sscanf(data, " %s %c %s", a, &operator, b) == 3) {
        double b_value, a_value;
        output_vector = &vectors[13];
        if (sscanf(a, "%lf", &a_value) == 1) {
            index_a = 11;
            set_vector(&vectors[11], a_value, a_value, a_value); 
        }else{
            index_a = contains_logic(a[0], vectors, &vector_count, 0);
            if(index_a == -1){
                printf("invalid vector\n");
                return 0;
            }
        }
        if (sscanf(b, "%lf", &b_value) == 1) {
            index_b = 12;
            set_vector(&vectors[12], b_value, b_value, b_value); 
        }else{
            index_b = contains_logic(b[0], vectors, &vector_count, 0);
            if(index_b == -1){
                printf("invalid vector\n");
                return 0;
            }
        } 
    // check for list
    }else if(strcmp(data, "list") == 0){
        for(int i=0; i<vector_count; i++){
            print(&vectors[i]);
        }
        return 0;
    // check for clear
    }else if(strcmp(data, "clear") == 0){
        memset(vectors, 0, sizeof vectors);
        vector_count = 0;
        return 0;
    // check for data by char
    }else if (sscanf(data, "%c", a) == 1){
        new_index = contains_logic(a[0], vectors, &vector_count, 0);
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
