/*
 * Filename: vector.h
 * Author: Noah Rethwisch
 * Created: 9/29/2026
 * Description: The header file for our math
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdio.h>

struct Vector{
    char identifier;
    double ijk[3];
};

void add(struct Vector *a,struct Vector *b,struct Vector *c);
void sub(struct Vector *a,struct Vector *b,struct Vector *c);
void mul(struct Vector *a,struct Vector *b,struct Vector *c);
void print(struct Vector *a);
void set_vector(struct Vector *a, double i, double j, double k);

#endif
