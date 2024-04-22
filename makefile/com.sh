#!/bin/bash

rm *.out
g++-13 -c src/Basic.cc -o Basic.o
g++-13 -c src/Vector.cc -o Vector.o
g++-13 -c src/Matrix.cc -o Matrix.o
g++-13 -c src/Tensor.cc -o Tensor.o
g++-13 -c test/test_04.cc -o test_04.o
g++-13 -o run.out test_04.o Basic.o Vector.o Matrix.o Tensor.o
rm *.o