#!/usr/bin/env bash

./xdrive_continuous     0.01 0.02 0.0001        -2 2   3 3       0.95  0.3 0.1   0 0.3
#./xdrive_continuous     0.01 0.02 0.0001        -2 2   2 2      0.95  0.4 0.1   0 0.3
#./xdrive_continuous     0.01 0.02 0.0001        -2 2   2 2 0.95  0.4 0.1   0 0.3

# plot the last of the simulation files
flist=(`ls sim*`)
length=${#flist[@]}
lastposition=$((length-1))
./plot_sims.py ${flist[${lastposition}]}

#    mu  = atof(argv[1]);
#    sdmu  = atof(argv[2]);
#    mu_drive = atof(argv[3]);
#    theta_f  = atof(argv[4]);
#    theta_m  = atof(argv[5]);
#    sd_f  = atof(argv[6]);
#    sd_m  = atof(argv[7]);
#    k  = atof(argv[8]);
#    cdm  = atof(argv[9]);
#    cdf  = atof(argv[10]);
#    h  = atof(argv[11]);
#    R  = atof(argv[12]);
