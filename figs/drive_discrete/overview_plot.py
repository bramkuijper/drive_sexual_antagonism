#!/usr/bin/env python3

import pandas as pd
import numpy as np
import scipy.ndimage 

import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from matplotlib.ticker import AutoMinorLocator

# set stylesheet
# should be present in matplotlib.get_configdir()/stylelib/$name.mplstyle
plt.style.use('base')
from matplotlib import rcParams
rcParams['font.family'] = 'Arial'

graphname = "overview_drive_discrete"


# single plot
def block(gridspec_stuff,
        row,
        col,
        data,
        yval='ssr',
        x_tickval=False,
        y_tickval=False
        ):

    global plt

    subsub = data[['tf','tm','ssr','faf','fxd']]

    # make pivot tables
    pivot_ssr = subsub.pivot_table(values=yval, index='tf', columns='tm')
    pivot_fxd = subsub.pivot_table(values='fxd', index='tf', columns='tm')
    pivot_faf = subsub.pivot_table(values='faf', index='tf', columns='tm')

    xo = pivot_ssr.columns.values
    yo = pivot_ssr.index.values
    x, y = np.meshgrid(xo, yo)

    ax = plt.subplot(
            gridspec_stuff[row, col]
            )

    ax.set_xlim((0,1))
    ax.set_ylim((0,1))

    if not x_tickval:
        plt.setp(ax.get_xticklabels(), visible=False)

    if not y_tickval:
        plt.setp(ax.get_yticklabels(), visible=False)

    # all the z-values for the different contours
    z_fxd = pivot_fxd.values
    z_faf = pivot_faf.values
    z = pivot_ssr.values

    # contourplots of sex ratio
    ax.contourf(x, y, z,
            np.arange(0, 1, 0.01),
            cmap='RdBu_r'
            )

    # set minor ticks
    minor_locator = AutoMinorLocator(5)
    ax.xaxis.set_minor_locator(minor_locator)
    ax.yaxis.set_minor_locator(minor_locator)

    # contour of the polymorphism for the sa loci
    ax.contour(x,y,z_faf,[0.01,0.99], colors='black',linewidths=0.5,linestyles='dashed')

    # contour of the polymorphism for the drive loci
    ax.contour(x,y,z_fxd,[0.01,0.99], colors='white',linewidths=1.0,linestyles="dotted")

    # contour line of the 50:50 sex-ratio
    ax.contour(x,y,z, [0.5], colors='black',linewidths=1.3)




# specify a grid with 3 rows and 3 columns
gs = gridspec.GridSpec(3, 3)

# import datafile
datafile = "iter_drive_30_5_2016_213530_917298101"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]

# cf = 0.2, cm = 0.2, k = 0.6, r = 0.5
datafile = "iter_drive_31_5_2016_162213_486055901"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 0, 0, sub, x_tickval=False, y_tickval=True)

# cf = 0.2, cm = 0.2, k = 0.8, r = 0.5
datafile = "iter_drive_31_5_2016_162654_848900616"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 0, 1, sub, x_tickval=False, y_tickval=False)

# cf = 0.2, cm = 0.2, k = 0.95, r = 0.5
datafile = "iter_drive_31_5_2016_163539_245811753"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 0, 2, sub, x_tickval=False, y_tickval=False)


# cf = 0.2, cm = 0.4, k = 0.6,  r = 0.5
datafile = "iter_drive_31_5_2016_165333_813986224"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 1, 0, sub, x_tickval=False, y_tickval=True)

# cf = 0.2, cm = 0.4, k = 0.8,  r = 0.5
datafile = "iter_drive_31_5_2016_225908_204240866"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 1, 1, sub, x_tickval=False, y_tickval=False)

# cf = 0.2, cm = 0.4, k = 0.95,  r = 0.5
datafile = "iter_drive_31_5_2016_225626_92149035"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == 0.5) & (the_data['type'] == "invade")]
block(gs, 1, 2, sub, x_tickval=False, y_tickval=False)


plt.savefig(graphname,format="pdf")



# specify a grid with 3 rows and 3 columns
gs = gridspec.GridSpec(3, 3)
h_val = 0

# import datafile
datafile = "iter_drive_30_5_2016_213530_917298101"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]

# cf = 0.2, cm = 0.2, k = 0.6, r = 0.5
datafile = "iter_drive_31_5_2016_162213_486055901"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 0, 0, sub, x_tickval=False, y_tickval=True)

# cf = 0.2, cm = 0.2, k = 0.8, r = 0.5
datafile = "iter_drive_31_5_2016_162654_848900616"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 0, 1, sub, x_tickval=False, y_tickval=False)

# cf = 0.2, cm = 0.2, k = 0.95, r = 0.5
datafile = "iter_drive_31_5_2016_163539_245811753"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 0, 2, sub, x_tickval=False, y_tickval=False)


# cf = 0.2, cm = 0.4, k = 0.6,  r = 0.5
datafile = "iter_drive_31_5_2016_165333_813986224"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 1, 0, sub, x_tickval=False, y_tickval=True)

# cf = 0.2, cm = 0.4, k = 0.8,  r = 0.5
datafile = "iter_drive_31_5_2016_225908_204240866"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 1, 1, sub, x_tickval=False, y_tickval=False)

# cf = 0.2, cm = 0.4, k = 0.95,  r = 0.5
datafile = "iter_drive_31_5_2016_225626_92149035"
the_data = pd.read_csv(datafile, sep=";")
sub = the_data[(the_data['h'] == h_val) & (the_data['type'] == "invade")]
block(gs, 1, 2, sub, x_tickval=False, y_tickval=False)


graphname = "overview_drive_discrete_h0.pdf"
plt.savefig(graphname,format="pdf")
