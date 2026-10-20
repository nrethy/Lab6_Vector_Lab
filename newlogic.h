/*
** Filename: newlogic.h
** Author: Noah Rethwisch
** Created: 10/14/2026
** Description: header for parsing logic
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vector.h"

int contains_logic(char identifier, struct Vector* array, int* length, int create);
char* logic(char data[]);
