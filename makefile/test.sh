#!/bin/bash

rm *.out
rm *.o
g++-13 -c src/Basic.cc -o Basic.o
g++-13 -mavx2 -g -c test/test_05.cc -o test_05.o
g++-13 -o run.out Basic.o test_05.o
rm *o