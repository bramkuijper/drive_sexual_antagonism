#!/usr/bin/env bash

./generate_drive.py

g++ -Wall -o xdrive drive2.cpp -lm -lrt
