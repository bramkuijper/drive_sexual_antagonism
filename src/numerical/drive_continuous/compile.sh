#!/usr/bin/env bash

./regexp.py expressions_resident.txt
./regexp.py expressions_fmatrix.txt
./regexp.py expressions_eigenvecs.txt
./regexp.py selgrad.txt

./generate_cpp.py

un=`uname`

lrtflag=''

if [ "${un}"=='Linux' ];
then lrtflag='-lrt'
fi

g++ -Wall -o xdrive_continuous drive_continuous2.cpp -lm "${lrtflag}" -lgsl -lgslcblas
