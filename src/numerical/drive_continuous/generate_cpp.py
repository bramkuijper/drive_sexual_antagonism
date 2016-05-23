#!/usr/bin/env python

import re

f = open("drive_continuous.cpp")
fl = f.read()
f.close()

f = open("expressions_resident.txt")
fl2 = f.read()
f.close()

f = open("expressions_eigenvecs.txt")
fl3 = f.read()
f.close()

fl = re.sub("EXPRESSIONS_RESIDENT",fl2, fl)
fl = re.sub("EXPRESSIONS_EIGENVECS",fl3, fl)

f = open("drive_continuous2.cpp","w")
f.write(fl)
f.close()
