#!/usr/bin/env bash

./generate_drive.py drive.cpp
g++ -Wall -o xdrive drive2.cpp -lm -lrt

./generate_drive.py drive_output.cpp
g++ -Wall -o xdrive_output drive_output2.cpp -lm -lrt

./generate_drive.py sa_only.cpp
g++ -Wall -o xsa_only sa_only2.cpp -lm -lrt
