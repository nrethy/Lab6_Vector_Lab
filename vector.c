/*
 * Filename: vector.c
 * Author: Noah Rethwisch
 * Created: 9/29/2026
 * Description: handles the math for the vectors
 */

#include <math.h>
#include <stdio.h>

struct Vector{
    char identifier;
    double ijk[3];
};

// a stores the result of the operation
// B and C are the values that we are adding
void add(struct Vector *a, struct Vector *b, struct Vector *c){
    a->ijk[0] = b->ijk[0] + c->ijk[0];
    a->ijk[1] = b->ijk[1] + c->ijk[1];
    a->ijk[2] = b->ijk[2] + c->ijk[2];
}

void sub(struct Vector *a, struct Vector *b, struct Vector *c){
    a->ijk[0] = b->ijk[0] - c->ijk[0];
    a->ijk[1] = b->ijk[1] - c->ijk[1];
    a->ijk[2] = b->ijk[2] - c->ijk[2];
}

void mul(struct Vector *a, struct Vector *b, struct Vector *c){
    a->ijk[0] = b->ijk[0] * c->ijk[0];
    a->ijk[1] = b->ijk[1] * c->ijk[1];
    a->ijk[2] = b->ijk[2] * c->ijk[2];
}

int dot(struct Vector *a, struct Vector *b){
    int dot_product = a->ijk[0] * b->ijk[0] + a->ijk[1] * b->ijk[1] + a->ijk[2] * b->ijk[2];
    return dot_product;
}

void print(struct Vector *a){
    printf("%c: %f, %f, %f\n", a->identifier, a->ijk[0], a->ijk[1], a->ijk[2]);
}
void set_vector(struct Vector *a, double i, double j, double k){
    a->ijk[0] = i;
    a->ijk[1] = j;
    a->ijk[2] = k;
}
