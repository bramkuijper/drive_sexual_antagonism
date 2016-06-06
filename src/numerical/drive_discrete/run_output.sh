#!/usr/bin/env bash

# good for getting a sex ratio that is still close to 0.5
#./xdrive_output 0.2 0.3     0.8 0.01     0.7 0.8 0.5
./xdrive_output 0.2 0.3     0.9 0.01     0.5 0.4 0

lslist=(`ls iter*`)

~/Projects/drive/figs/single_sim/plot_single_sim.py ${lslist[-1]}
#    double cf = atof(argv[1]);
#    double cm = atof(argv[2]);
#    double kdrive = atof(argv[3]);
#    double r = atof(argv[4]);
#    double tf = atof(argv[5]);
#    double tm = atof(argv[6]);
#    double h = atof(argv[7]);

