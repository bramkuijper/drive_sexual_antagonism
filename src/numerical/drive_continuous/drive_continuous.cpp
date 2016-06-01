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
    double cfd = atof(argv[6]);
    double cmd = atof(argv[7]);
    double h = atof(argv[8]);
    double r = atof(argv[9]);

    double x1 = 0;
    double x2 = 0;
    double selgrad = 0;
    double x1mtplus1 = 0;


    // mutant values
    double x1m = 0;
    double x2m = 0;

    double E = exp(1);

    double ff_X_X1_tplus1, ff_X_X2_tplus1, 
           ff_Xd_X1_tplus1, ff_Xd_X2_tplus1, 
           fm_X_X1_tplus1, fm_X_X2_tplus1, 
           fm_Xd_X1_tplus1, fm_Xd_X2_tplus1, fm_Y_tplus1;

    double ff_X_X1, ff_X_X2, 
           ff_Xd_X1, ff_Xd_X2, 
           fm_X_X1, fm_X_X2, 
           fm_Xd_X1, fm_Xd_X2, fm_Y;

    double uf0, uf1, um0, um1;
    double vf0, vf1, vm0, vm1;

    double lambda = 100;
 
    ff_X_X1 = ff_X_X2 = 
           ff_Xd_X1 = ff_Xd_X2 = 0.25;

    fm_X_X1 = fm_X_X2 = 
           fm_Xd_X1 = fm_Xd_X2 = fm_Y = 1.0/5;

    double X1, X2, Xd, X, Y;

    double bound = 1e-07;

    int maxt = 10000000;
    int tx2;

    DataFile << "time;ff_X_X1;ff_X_X2;ff_Xd_X1;ff_Xd_X2;fm_X_X1;fm_X_X2;fm_Xd_X1;fm_Xd_X2;fm_Y;uf0;uf1;um0;um1;vf0;vf1;vm0;vm1;X1;X2;Xd;X;Y;x1;ev;" << endl;

    for (int tx = 0; tx < maxt; ++tx)
    {
        // first update the resident frequencies
        for (tx2 = 0; tx2 < maxt; ++tx2)
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
                ff_X_X1 = ff_X_X1_tplus1;
                ff_X_X2 = ff_X_X2_tplus1;
                ff_Xd_X1 = ff_Xd_X1_tplus1;
                ff_Xd_X2 = ff_Xd_X2_tplus1;

                fm_X_X1 = fm_X_X1_tplus1;
                fm_X_X2 = fm_X_X2_tplus1;
                fm_Xd_X1 = fm_Xd_X1_tplus1;
                fm_Xd_X2 = fm_Xd_X2_tplus1;
                fm_Y = fm_Y_tplus1;
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

        EXPRESSIONS_MATRIX_F

          gsl_matrix_view m 
            = gsl_matrix_view_array (data, 4, 4);

          gsl_vector_complex *eval = gsl_vector_complex_alloc (4);
          gsl_matrix_complex *evec = gsl_matrix_complex_alloc (4, 4);

          gsl_eigen_nonsymmv_workspace * w = 
            gsl_eigen_nonsymmv_alloc (4);
          
          gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

          gsl_eigen_nonsymmv_free (w);

          gsl_eigen_nonsymmv_sort (eval, evec, 
                                   GSL_EIGEN_SORT_ABS_DESC);
              

        lambda = GSL_REAL(gsl_vector_complex_get(eval, 0));


        EXPRESSIONS_EIGENVECS


//        cout << uf0 << ";" << uf1 << ";" << um0 << ";" << um1 << endl;
//        cout << vf0 << ";" << vf1 << ";" << vm0 << ";" << vm1 << endl;


        selgrad = SELGRAD;

        // evolution of mutant
        x1mtplus1 = x1 + selgrad;

        if (fabs(x1mtplus1 - x1) < 1e-12 || isnan(selgrad) != 0)
        {
            x1 = x1mtplus1;
        
            X1 = ff_X_X1 + ff_Xd_X1;
            X2 = ff_X_X2 + ff_Xd_X2;
            Xd = ff_Xd_X1 + ff_Xd_X2;
            X = ff_X_X1 + ff_X_X2;
            Y = fm_Y;


            DataFile << tx2 << ";"
                        << ff_X_X1 << ";" 
                        << ff_X_X2 << ";" 
                        << ff_Xd_X1 << ";" 
                        << ff_Xd_X2 << ";" 
                        << fm_X_X1 << ";" 
                        << fm_X_X2 << ";" 
                        << fm_Xd_X1 << ";" 
                        << fm_Xd_X2 << ";"
                        << fm_Y << ";"
                        << uf0 << ";"
                        << uf1 << ";"
                        << um0 << ";"
                        << um1 << ";"
                        << vf0 << ";"
                        << vf1 << ";"
                        << vm0 << ";"
                        << vm1 << ";"
                        << X1 << ";"
                        << X2 << ";"
                        << Xd << ";"
                        << X << ";"
                        << Y << ";" 
                        << x1 << ";" 
                        << lambda << ";" << endl;

            break;
        }

        x1 = x1mtplus1;

        X1 = ff_X_X1 + ff_Xd_X1;
        X2 = ff_X_X2 + ff_Xd_X2;
        Xd = ff_Xd_X1 + ff_Xd_X2;
        X = ff_X_X1 + ff_X_X2;
        Y = fm_Y;

            DataFile << tx2 << ";"
                        << ff_X_X1 << ";" 
                        << ff_X_X2 << ";" 
                        << ff_Xd_X1 << ";" 
                        << ff_Xd_X2 << ";" 
                        << fm_X_X1 << ";" 
                        << fm_X_X2 << ";" 
                        << fm_Xd_X1 << ";" 
                        << fm_Xd_X2 << ";"
                        << fm_Y << ";"
                        << uf0 << ";"
                        << uf1 << ";"
                        << um0 << ";"
                        << um1 << ";"
                        << vf0 << ";"
                        << vf1 << ";"
                        << vm0 << ";"
                        << vm1 << ";"
                        << X1 << ";"
                        << X2 << ";"
                        << Xd << ";"
                        << X << ";"
                        << Y << ";" 
                        << x1 << ";" 
                        << lambda << ";" << endl;
    }

    DataFile << endl << endl
        << "kappa;" << kappa << endl
        << "sv;" << sv << endl
        << "th_f;" << th_ff << endl
        << "th_m;" << th_m << endl
        << "cmd;" << cmd << endl
        << "cfd;" << cfd << endl
        << "h;" << h << endl
        << "k;" << k << endl
        << "r;" << r << endl;
}
