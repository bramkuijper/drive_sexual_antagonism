#!/usr/bin/env python

import re

f = open("drive_continuous.cpp")
fl = f.read()
f.close()

f = open("expressions_resident.txt")
fl2 = f.read()
f.close()

f = open("expressions_eigenvecs_x1m.txt")
fl_ev_x1m = f.read()
f.close()

f = open("expressions_eigenvecs_x2m.txt")
fl_ev_x2m = f.read()
f.close()

f = open("selgrad_x1m.txt")
fl_selgrad_x1m = f.read()
f.close()

f = open("selgrad_x2m.txt")
fl_selgrad_x2m = f.read()
f.close()

f = open("expressions_fmatrix_x1m.txt")
fl_fmat_x1m = f.read()
f.close()

f = open("expressions_fmatrix_x2m.txt")
fl_fmat_x2m = f.read()
f.close()

fl = re.sub("EXPRESSIONS_RESIDENT",fl2, fl)
fl = re.sub("EXPRESSIONS_EIGENVECS_X1M",fl_ev_x1m, fl)
fl = re.sub("EXPRESSIONS_EIGENVECS_X2M",fl_ev_x2m, fl)
fl = re.sub("SELGRAD_X1M", fl_selgrad_x1m, fl)
fl = re.sub("SELGRAD_X2M", fl_selgrad_x2m, fl)
fl = re.sub("EXPRESSIONS_MATRIX_F_X1M",fl_fmat_x1m, fl)
fl = re.sub("EXPRESSIONS_MATRIX_F_X2M",fl_fmat_x2m, fl)

f = open("drive_continuous2.cpp","w")
f.write(fl)
f.close()
