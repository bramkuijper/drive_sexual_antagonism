#!/usr/bin/env python3

import sys, re, os.path
import pandas as pd
import matplotlib

import numpy as np
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from pylab import *

params={'axes.linewidth' : .5}
rcParams.update(params)

# get the filename from the command line
filename = sys.argv[1]

filename = sys.argv[1]

f = open(filename);
fl = f.readlines();
f.close()


parline = -1

for idx, line in enumerate(fl):
    if re.match("^mu.*",line) != None:
        parline = idx - 1;
        break;

# read in the csv file
if parline > 0:
    histdat = pd.read_csv(filename, nrows=parline-3, sep=";")
else:
    histdat = pd.read_csv(filename, sep=";")

# only take every tenth generation, otherwise too much data....
#histdat = histdat[histdat["generation"] % 10 == 0]

# generate the figure

# initialize and specify size 
fig = plt.figure(figsize=(10,10))

num_rows = 3

# add first subplot
plt.subplot(num_rows,1,1)
plt.plot(histdat["generation"],histdat["meanz"],'b')
plt.tick_params(axis='x',which='both',bottom='on',top='on',labelbottom='off')
plt.ylabel(r'elevation, $\bar{z}$')

# add second subplot
plt.subplot(num_rows,1,2)
plt.plot(histdat["generation"],histdat["pXd"],'b',
        histdat["generation"],histdat["pY"],'r',
        linewidth=1)
plt.tick_params(axis='x',which='both',bottom='on',top='on',labelbottom='off')
plt.ylabel(r'drive and Y')
plt.legend((r'$p_{X_{d}}$',r'$p_{Y}$'))
plt.ylim(-0.05,1.05)

# add third subplot
plt.subplot(num_rows,1,3)
plt.plot(histdat["generation"],histdat["Nf"],'magenta',
        histdat["generation"],histdat["Nm"],'green',
        linewidth=1)
plt.tick_params(axis='x',which='both',bottom='on',top='on',labelbottom='off')
plt.ylabel(r'population size, $\bar{m}_{ij}$')
plt.legend((r'$N_{f}$',r'$N_{m}$'))

graphname = os.path.dirname(filename)
if graphname != '':
    graphname += "/"
graphname += "graph_" + os.path.basename(filename) + ".pdf"

plt.savefig(graphname,format="pdf")
