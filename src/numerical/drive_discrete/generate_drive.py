#!/usr/bin/env python

import os, re, sys

# file with the mathematica expressions
filename_exp = "drive_expressions.txt"

# C++ file
filename_c = sys.argv[1]

# the necessary regexps
regexps = [(r"(x|y)\((\d+)\)","\\1\\2")]

f = open(filename_exp)
fl = f.read()
f.close()

for regexp_i in regexps:
    fl = re.sub(regexp_i[0],regexp_i[1],fl)


print(fl)

f = open(filename_c)
fl2 = f.read()
f.close()

fl2 = re.sub("ITERATIONS_HERE",fl,fl2)

newfile = os.path.splitext(filename_c)[0]

f = open(newfile + "2.cpp","w")

f.write(fl2)

f.close()
