#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>
#include <cassert>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "bramauxiliary.h"


//#define NDEBUG

using namespace std;

// give the outputfile a unique name based on a timestamp
// involving nanoseconds
// by using the create_filename function (see 
// "bramauxiliary.h")
string filename("iter_drive_continous");
string filename_new(create_filename(filename));
ofstream DataFile(filename_new.c_str());  // output file 




int main(int argc, char **argv)
{
    double kappa = atof(argv[1]);
    double sv = atof(argv[2]);
    double k = atof(argv[3]);
    double th_ff = atof(argv[4]);
    double th_m = atof(argv[5]);
    double cmd = atof(argv[6]);
    double cfd = atof(argv[7]);
    double h = atof(argv[8]);
    double r = atof(argv[9]);

    double x1 = 0;
    double x2 = 0;

    double E = exp(1);

    double ff_X_X1_tplus1, ff_X_X2_tplus1, 
           ff_Xd_X1_tplus1, ff_Xd_X2_tplus1, 
           fm_X_X1_tplus1, fm_X_X2_tplus1, 
           fm_Xd_X1_tplus1, fm_Xd_X2_tplus1, fm_Y_tplus1;

    double ff_X_X1, ff_X_X2, 
           ff_Xd_X1, ff_Xd_X2, 
           fm_X_X1, fm_X_X2, 
           fm_Xd_X1, fm_Xd_X2, fm_Y;
 
    ff_X_X1 = ff_X_X2 = 
           ff_Xd_X1 = ff_Xd_X2 = 0.25;

    fm_X_X1 = fm_X_X2 = 
           fm_Xd_X1 = fm_Xd_X2 = fm_Y = 1.0/5;

    double bound = 1e-07;

    int maxt = 10000000;

    DataFile << "ff_X_X1;ff_X_X2;ff_Xd_X1;ff_Xd_X2;fm_X_X1;fm_X_X2;fm_Xd_X1;fm_Xd_X2;" << endl;

    for (int tx = 0; tx < maxt; ++tx)
    {
        // first update the resident frequencies
        for (int tx2 = 0; tx2 < maxt; ++tx2)
        {
            EXPRESSIONS_RESIDENT


            if (
                    fabs(ff_X_X1_tplus1 - ff_X_X1) < bound &&
                    fabs(ff_X_X2_tplus1 - ff_X_X2) < bound &&
                    fabs(ff_Xd_X1_tplus1 - ff_Xd_X1) < bound &&
                    fabs(ff_Xd_X2_tplus1 - ff_Xd_X2) < bound &&
                    fabs(fm_X_X1_tplus1 - fm_X_X1) < bound &&
                    fabs(fm_X_X2_tplus1 - fm_X_X2) < bound &&
                    fabs(fm_Xd_X1_tplus1 - fm_Xd_X1) < bound &&
                    fabs(fm_Xd_X2_tplus1 - fm_Xd_X2) < bound &&
                    fabs(fm_Y_tplus1 - fm_Y) < bound
            )
            {
                break;
            }
    
            ff_X_X1 = ff_X_X1_tplus1;
            ff_X_X2 = ff_X_X2_tplus1;
            ff_Xd_X1 = ff_Xd_X1_tplus1;
            ff_Xd_X2 = ff_Xd_X2_tplus1;

            fm_X_X1 = fm_X_X1_tplus1;
            fm_X_X2 = fm_X_X2_tplus1;
            fm_Xd_X1 = fm_Xd_X1_tplus1;
            fm_Xd_X2 = fm_Xd_X2_tplus1;
            fm_Y = fm_Y_tplus1;
        }

        EXPRESSIONS_EIGENVECS

    }
}
