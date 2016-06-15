#!/usr/bin/env python

import numpy as np

cf = list(np.arange(0,0.5,0.1))
cm = list(np.arange(0,0.5,0.1))
r = list(np.arange(0.1,0.5,0.1)) + [ 0.01]
kdrive = list(np.arange(0.6,1.0,0.1)) + [ 0.95 ]

exe = "./xdrive"


ctr = 1
for cf_i in cf:
    for cm_i in cm:
        if cf_i > cm_i:
            continue
        for r_i in r:
            for kdrive_i in kdrive:

#                print(str(cm_i) + " "  + str(cf_i))

                pe = .5 * (2 * kdrive_i * (1-cm_i) * 1 + 1 * (1 - 2 * 1)) / (2 * kdrive_i* ( (1-cm_i) * (1 - (1-cf_i))))
#
                if pe < 0.01 or pe > 0.99:
                    continue
#
                print("echo " + str(ctr))
                ctr+=1

                print(exe + " " + str(cf_i) + " " + str(cm_i) + " " + str(kdrive_i) + " " + str(r_i))

