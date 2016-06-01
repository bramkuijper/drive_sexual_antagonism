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

    double x1 = th_ff;
    double x2 = th_m;
    double selgrad_x1m = 0;
    double selgrad_x2m = 0;
    double x1mtplus1 = 0;
    double x2mtplus1 = 0;

    bool x1minvade = true;
    bool x1converged = false;
    bool x2converged = false;


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

    double uf0x1m, uf1x1m, um0x1m, um1x1m;
    double uf0x2m, uf1x2m, um0x2m, um1x2m;
    double vf0x1m, vf1x1m, vm0x1m, vm1x1m;
    double vf0x2m, vf1x2m, vm0x2m, vm1x2m;

    double lambdax1m = 100;
    double lambdax2m = 100;
 
    ff_X_X1 = ff_X_X2 = 
           ff_Xd_X1 = ff_Xd_X2 = 0.25;

    fm_X_X1 = fm_X_X2 = 
           fm_Xd_X1 = fm_Xd_X2 = fm_Y = 1.0/5;

    double X1, X2, Xd, X, Y;

    double bound = 1e-07;

    int maxt = 10000000;
    int tx2;
    DataFile << "time;time2;ff_X_X1;ff_X_X2;ff_Xd_X1;ff_Xd_X2;fm_X_X1;fm_X_X2;fm_Xd_X1;fm_Xd_X2;fm_Y;uf0x1m;uf1x1m;um0x1m;um1x1m;vf0x1m;vf1x1m;vm0x1m;vm1x1m;uf0x2m;uf1x2m;um0x2m;um1x2m;vf0x2m;vf1x2m;vm0x2m;vm1x2m;X1;X2;Xd;X;Y;x1;x2;evx1m;evx2m;" << endl;

    //cout << "time;ff_X_X1;ff_X_X2;ff_Xd_X1;ff_Xd_X2;fm_X_X1;fm_X_X2;fm_Xd_X1;fm_Xd_X2;fm_Y;" << endl;
    for (int tx = 0; tx < maxt; ++tx)
    {
        // first update the resident frequencies
        for (tx2 = 0; tx2 < maxt; ++tx2)
        {
            EXPRESSIONS_RESIDENT


            // if boundary reached exit iterations
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

            X1 = ff_X_X1_tplus1 + ff_Xd_X1_tplus1;
            X2 = ff_X_X2_tplus1 + ff_Xd_X2_tplus1;
                        
            
            cout << tx2 << ";" << ff_X_X1 << ";" 
                        << ff_X_X2 << ";" 
                        << ff_Xd_X1 << ";" 
                        << ff_Xd_X2 << ";" 
                        << fm_X_X1 << ";" 
                        << fm_X_X2 << ";" 
                        << fm_Xd_X1 << ";" 
                        << fm_Xd_X2 << ";"
                        << fm_Y << ";" 
                        << X1 << ";" 
                        << X2 << ";" 
                        << endl;
        }// end tx2

        x1minvade = !x1minvade;

        if (x1minvade)
        {

            EXPRESSIONS_MATRIX_F_X1M

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
                  

            lambdax1m = GSL_REAL(gsl_vector_complex_get(eval, 0));


            EXPRESSIONS_EIGENVECS_X1M


    //        cout << uf0 << ";" << uf1 << ";" << um0 << ";" << um1 << endl;
    //        cout << vf0 << ";" << vf1 << ";" << vm0 << ";" << vm1 << endl;


            selgrad_x1m = SELGRAD_X1M;

            // evolution of mutant
            x1mtplus1 = x1 + selgrad_x1m;

            x1converged = fabs(x1mtplus1 - x1) < bound;
            
            x1 = x1mtplus1;
        } else
        {
            EXPRESSIONS_MATRIX_F_X2M

              gsl_matrix_view m 
                = gsl_matrix_view_array (data, 4, 4);

              gsl_vector_complex *eval = gsl_vector_complex_alloc(4);
              gsl_matrix_complex *evec = gsl_matrix_complex_alloc(4, 4);

              gsl_eigen_nonsymmv_workspace * w = gsl_eigen_nonsymmv_alloc (4);
              
              gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

              gsl_eigen_nonsymmv_free (w);

              gsl_eigen_nonsymmv_sort (eval, evec, 
                                       GSL_EIGEN_SORT_ABS_DESC);
                  

            lambdax2m = GSL_REAL(gsl_vector_complex_get(eval, 0));


            EXPRESSIONS_EIGENVECS_X2M


    //        cout << uf0 << ";" << uf1 << ";" << um0 << ";" << um1 << endl;
    //        cout << vf0 << ";" << vf1 << ";" << vm0 << ";" << vm1 << endl;


            selgrad_x2m = SELGRAD_X2M;

            // evolution of mutant
            x2mtplus1 = x2 + selgrad_x2m;
            
            x2converged = fabs(x2mtplus1 - x2) < bound;

            x2 = x2mtplus1;
        }

        if ((x1converged && x2converged) || (isnan(selgrad_x1m) != 0 || isnan(selgrad_x2m) != 0))
        {
            X1 = ff_X_X1 + ff_Xd_X1;
            X2 = ff_X_X2 + ff_Xd_X2;
            Xd = ff_Xd_X1 + ff_Xd_X2;
            X = ff_X_X1 + ff_X_X2;
            Y = fm_Y;


            DataFile << tx << ";" << tx2 << ";"
                        << ff_X_X1 << ";" 
                        << ff_X_X2 << ";" 
                        << ff_Xd_X1 << ";" 
                        << ff_Xd_X2 << ";" 
                        << fm_X_X1 << ";" 
                        << fm_X_X2 << ";" 
                        << fm_Xd_X1 << ";" 
                        << fm_Xd_X2 << ";"
                        << fm_Y << ";"
                        << uf0x1m << ";"
                        << uf1x1m << ";"
                        << um0x1m << ";"
                        << um1x1m << ";"
                        << vf0x1m << ";"
                        << vf1x1m << ";"
                        << vm0x1m << ";"
                        << vm1x1m << ";"
                        << uf0x2m << ";"
                        << uf1x2m << ";"
                        << um0x2m << ";"
                        << um1x2m << ";"
                        << vf0x2m << ";"
                        << vf1x2m << ";"
                        << vm0x2m << ";"
                        << vm1x2m << ";"
                        << X1 << ";"
                        << X2 << ";"
                        << Xd << ";"
                        << X << ";"
                        << Y << ";" 
                        << x1 << ";" 
                        << x2 << ";" 
                        << lambdax1m << ";" 
                        << lambdax2m << ";" 
                        << endl;

            break;
        }

        X1 = ff_X_X1 + ff_Xd_X1;
        X2 = ff_X_X2 + ff_Xd_X2;
        Xd = ff_Xd_X1 + ff_Xd_X2;
        X = ff_X_X1 + ff_X_X2;
        Y = fm_Y;


            DataFile << tx << ";" << tx2 << ";"
                        << ff_X_X1 << ";" 
                        << ff_X_X2 << ";" 
                        << ff_Xd_X1 << ";" 
                        << ff_Xd_X2 << ";" 
                        << fm_X_X1 << ";" 
                        << fm_X_X2 << ";" 
                        << fm_Xd_X1 << ";" 
                        << fm_Xd_X2 << ";"
                        << fm_Y << ";"
                        << uf0x1m << ";"
                        << uf1x1m << ";"
                        << um0x1m << ";"
                        << um1x1m << ";"
                        << vf0x1m << ";"
                        << vf1x1m << ";"
                        << vm0x1m << ";"
                        << vm1x1m << ";"

                        << uf0x2m << ";"
                        << uf1x2m << ";"
                        << um0x2m << ";"
                        << um1x2m << ";"
                        << vf0x2m << ";"
                        << vf1x2m << ";"
                        << vm0x2m << ";"
                        << vm1x2m << ";"
                        << X1 << ";"
                        << X2 << ";"
                        << Xd << ";"
                        << X << ";"
                        << Y << ";" 
                        << x1 << ";" 
                        << x2 << ";" 
                        << lambdax1m << ";" 
                        << lambdax2m << ";" 
                        << endl;
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
