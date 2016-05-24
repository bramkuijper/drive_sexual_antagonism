#!/usr/bin/env python

kappa = [ 0, 1.0 ]
sv = [ 0, 1, 2, 3 ]
k = [ 0.5, 0.6, 0.7, 0.8, 0.9, 0.95 ]
th_ff = -2
th_m = -2
cfd = [ 0, 0.1, 0.2, 0.3, 0.4 ]
cmd = [ 0.1, 0.2, 0.3, 0.4 ]
h = [ 0, 0.25, 0.5 ]
r = [ 0, 0.1, 0.2, 0.3, 0.4, 0.5 ]

exe = "./xdrive_continuous"

ctr = 0
for kappa_i in kappa:
    for sv_i in sv:
        for k_i in k:
            for cfd_i in cfd:
                for cmd_i in cmd:
                    for h_i in h:
                        for r_i in r:
                            ctr += 1

                            print("echo " + str(ctr))
                            print(exe + " " + str(kappa_i) + " " + str(sv_i) + " " + str(k_i) + " " + str(th_ff) 
                                    + " " + str(th_m) + " "  + str(cfd_i) + " " + str(cmd_i) + " " + str(h_i) + " " + str(r_i))

