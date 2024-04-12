#!/bin/bash

rm *.o
rm *.out

g++ -c src/Basic.cc -o Basic.o
g++ -c src/Vector.cc -o Vector.o
g++ -c src/Matrix.cc -o Matrix.o
g++ -c test/test_04.cc -o test_04.o
g++ -o run.out test_04.o Basic.o Vector.o Matrix.o
