#!/share/apps/python-3.5.1/bin/python3

import re, sys

f = open(sys.argv[1])
fl = f.read()
f.close()

relist = [ ('λ','lambda'), ('κ','kappa'),('\(List\((Y)\)\)',r'_\1'),('\(List\((Xd|X),(X1|X2)\)\)',r'_\1_\2'),('Power','pow'),('th\((ff|m)\)',r'th_\1')]

for re_i in relist:
    fl = re.sub(re_i[0],re_i[1],fl)

f = open(sys.argv[1],"w")
f.write(fl)
f.close()
