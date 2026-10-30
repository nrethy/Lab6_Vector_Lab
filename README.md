# Lab6_Vector_Lab Noah Rethwisch

This lab is designed to serve as a calculator for vectors

## Compiling

run make to compile using the makefile

## Features

- Uses a pointer to store the vectors, allowing for as many vectors as there
  are letters
- Reads and writes the vectors to CSV files

## Commands Supported

- a = 1 2 3 : You can provide any letter and assign to it a vector value
- a = a + b : you can do a vector operation that outputs to a vector
  - Various operations can be performed including addition(+)
    multiplication(*) and subtraction(-) by modifying the operator
  - a + 1 : Scalar operations can also be performed by using numbers to replace
    vectors
- a + b : you can do a vector operation that does not output to a vector
  - note that the same operations as before can be performed
- clear : This will clear any stored vectors
- list : This will list stored vectors
- a : using the name of any vector(a in this example) you can print the values
  in the vector
- load <filename.csv> : this can be used to load vectors from a csv file
- save <filename.csv> : this will save vectors to a csv file
- quit : this will exit the program

## Dynamic Memory

This program makes use of dynamic memorie and pointers by storing vectors in a pointer, which can store up to 52 vectors

