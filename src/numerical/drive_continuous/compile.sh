#!/usr/bin/env bash

./regexp.py expressions_resident.txt
./regexp.py expressions_F.txt

./generate_cpp.py

un=`uname`

lrtflag=''

if [ "${un}"=='Linux' ];
then lrtflag='-lrt'
fi

g++ -Wall -o xdrive_continuous drive_continuous2.cpp -lm "${lrtflag}" -lgsl -lgslcblas
