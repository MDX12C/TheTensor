#!/bin/bash

rm *.out
rm *.o
g++-13 -mavx2 -g ./test/test_02.cc
