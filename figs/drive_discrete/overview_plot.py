#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.ndimage 

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.ticker import AutoMinorLocator

import block

graphname = "overview_drive_discrete"


# specify a grid with 3 rows and 2 columns
gs = gridspec.GridSpec(3, 2)

b = block.Block(gs)

# 
datafile = "runs_cfcm.csv"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]

row = col = 0

sub_1 = sub[(sub["cm"] == 0.2) & (sub["r"] == 0.4)]

b.block(
        row=row,
        col=col,
        data=sub_1,
        x_tickval=False,
        y_tickval=True)

col = 1 
b.block(
        row=row,
        col=col,
        yval="fxd",
        data=sub_1,
        x_tickval=False,
        y_tickval=True)

row = 1
col = 0

b.block(
        row=row,
        col=col,
        data=sub[sub['cm'] == 0.4 ],
        x_tickval=False,
        y_tickval=True)

col = 1 
b.block(
        row=row,
        col=col,
        yval="fxd",
        data=sub[sub['cm'] == 0.4 ],
        x_tickval=False,
        y_tickval=True)

row = 2
col = 0

sub_2 = sub[(sub["cm"] == 0.3) & (sub["r"] == 0.1)]
b.block(
        row=row,
        col=col,
        data=sub_2,
        x_tickval=False,
        y_tickval=True)

col = 1 
b.block(
        row=row,
        col=col,
        yval="fxd",
        data=sub_2,
        x_tickval=False,
        y_tickval=True)

plt.savefig(graphname,format="pdf")

