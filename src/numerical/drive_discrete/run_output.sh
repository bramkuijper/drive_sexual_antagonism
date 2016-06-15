#!/usr/bin/env bash

# good for getting a sex ratio that is still close to 0.5
#./xdrive_output 0.2 0.3     0.8 0.01     0.7 0.8 0.5
./xdrive_output 0.3 0.3     0.95 0.01     0.4 0.5 0.5

lslist=(`find . -maxdepth 1 -amin -10 -iname "iter_drive_output*"`)

for val in ${lslist[@]};
do ~/Projects/drive/figs/single_sim/plot_single_sim.py $val;
done;

#    double cf = atof(argv[1]);
#    double cm = atof(argv[2]);
#    double kdrive = atof(argv[3]);
#    double r = atof(argv[4]);
#    double tf = atof(argv[5]);
#    double tm = atof(argv[6]);
#    double h = atof(argv[7]);

