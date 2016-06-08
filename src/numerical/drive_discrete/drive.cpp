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
#include "bramauxiliary.h"


//#define NDEBUG

using namespace std;

// give the outputfile a unique name based on a timestamp
// involving nanoseconds
// by using the create_filename function (see 
// "bramauxiliary.h")
string filename("iter_drive");
string filename_new(create_filename(filename));
ofstream DataFile(filename_new.c_str());  // output file 

int main(int argc, char **argv)
{
    double cf = atof(argv[1]);
    double cm = atof(argv[2]);
    double kdrive = atof(argv[3]);
    double r = atof(argv[4]);

    double x1, x2, x3, x4;
    double y1, y2, y3, y4, y5, psr, ssr;
    double xtp1, xtp2, xtp3, xtp4;
    double ytp1, ytp2, ytp3, ytp4, ytp5;

    double pe, ps, qe, qs;
    double Dz, Demax, Dsmax, Dzprime; 

    double bound = 1e-07;
    int maxt = 10000000;

    DataFile << "type;t;tf;tm;h;cf;cm;kdrive;r;Dz;Demax;Dsmax;Dzprime;y1;y2;y3;y4;y5;x1;x2;x3;x4;psr;ssr;fxd;faf;mxd;maf;" << endl;

    for (double tf = 0; tf <= 1.0; tf+=0.02)
    {
        for (double tm = 0; tm <= 1.0; tm+=0.02)
        {
            for (double h = 0; h <= 1.0; h+= 0.1)
            {
                x1 = 0.5;
                x2 = 0;
                x3 = 0.5;
                x4 = 0;
                
                y1 = 0.25;
                y2 = 0;
                y3 = 0.25;
                y4 = 0;
                y5 = 0.5;

                int t;
                for (t = 0; t <= maxt; ++t)
                {
                    ITERATIONS_HERE

                    if (
                            fabs(ytp1 - y1) <= bound &&
                            fabs(ytp2 - y2) <= bound &&
                            fabs(ytp3 - y3) <= bound &&
                            fabs(ytp4 - y4) <= bound &&
                            fabs(ytp5 - y5) <= bound &&
                            fabs(xtp1 - x1) <= bound &&
                            fabs(xtp2 - x2) <= bound &&
                            fabs(xtp3 - x3) <= bound &&
                            fabs(xtp4 - x4) <= bound
                    ) 
                    {
                        // calculate frequency Af
                        pe = x1 + x3;
                        qe = x3 + x4;
                        ps = y1 + y3;
                        qs = y3 + y4;

                        Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                        Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                        Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                        Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));


                        DataFile << "init;" 
                            << t << ";" 
                            << tf << ";" 
                            << tm << ";" 
                            << h << ";" 
                            << cf << ";" 
                            << cm << ";" 
                            << kdrive << ";" 
                            << r << ";"
                            << Dz << ";"
                            << Demax << ";"
                            << Dsmax << ";"
                            << Dzprime << ";"
                            << y1 << ";" 
                            << y2 << ";" 
                            << y3 << ";" 
                            << y4 << ";" 
                            << y5 << ";"
                            << x1 << ";" 
                            << x2 << ";" 
                            << x3 << ";" 
                            << x4 << ";" 
                            << psr << ";" 
                            << ssr << ";"
                            << x3 + x4 << ";" 
                            << x1 + x3 << ";" 
                            << y3 + y4 << ";" 
                            << y1 + y3 << ";" << endl;
                        break;
                    }
                    else
                    {
                        y1 = ytp1;
                        y2 = ytp2;
                        y3 = ytp3;
                        y4 = ytp4;
                        y5 = ytp5;
                        x1 = xtp1;
                        x2 = xtp2;
                        x3 = xtp3;
                        x4 = xtp4;
                    }
                }

                // no convergence, odd.
                if (t==maxt)
                {
                        // calculate frequency Af
                        pe = x1 + x3;
                        qe = x3 + x4;
                        ps = y1 + y3;
                        qs = y3 + y4;

                        Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                        Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                        Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                        Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));


                        DataFile << "init;" 
                            << t << ";" 
                            << tf << ";" 
                            << tm << ";" 
                            << h << ";" 
                            << cf << ";" 
                            << cm << ";" 
                            << kdrive << ";" 
                            << r << ";"
                            << Dz << ";"
                            << Demax << ";"
                            << Dsmax << ";"
                            << Dzprime << ";"
                            << y1 << ";" 
                            << y2 << ";" 
                            << y3 << ";" 
                            << y4 << ";" 
                            << y5 << ";"
                            << x1 << ";" 
                            << x2 << ";" 
                            << x3 << ";" 
                            << x4 << ";" 
                            << psr << ";" 
                            << ssr << ";"
                            << x3 + x4 << ";" 
                            << x1 + x3 << ";" 
                            << y3 + y4 << ";" 
                            << y1 + y3 << ";" << endl;
                }

                assert(x2 == 0);
                assert(x4 == 0);

                x2 = 0.000005; 
                x4 = 0.000005;
                
                y2 = 0.000005; 
                y4 = 0.000005;

                for (t = 0; t <= maxt; ++t)
                {
                    ITERATIONS_HERE

                    if (
                            fabs(ytp1 - y1) <= bound &&
                            fabs(ytp2 - y2) <= bound &&
                            fabs(ytp3 - y3) <= bound &&
                            fabs(ytp4 - y4) <= bound &&
                            fabs(ytp5 - y5) <= bound &&
                            fabs(xtp1 - x1) <= bound &&
                            fabs(xtp2 - x2) <= bound &&
                            fabs(xtp3 - x3) <= bound &&
                            fabs(xtp4 - x4) <= bound
                    ) 
                    {
                        // calculate frequency Af
                        pe = x1 + x3;
                        qe = x3 + x4;
                        ps = y1 + y3;
                        qs = y3 + y4;

                        Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                        Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                        Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                        Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));

                        DataFile << "invade;" 
                            << t << ";" 
                            << tf << ";" 
                            << tm << ";" 
                            << h << ";" 
                            << cf << ";" 
                            << cm << ";" 
                            << kdrive << ";" 
                            << r << ";"
                            << Dz << ";"
                            << Demax << ";"
                            << Dsmax << ";"
                            << Dzprime << ";"
                            << y1 << ";" 
                            << y2 << ";" 
                            << y3 << ";" 
                            << y4 << ";" 
                            << y5 << ";"
                            << x1 << ";" 
                            << x2 << ";" 
                            << x3 << ";" 
                            << x4 << ";" 
                            << psr << ";" 
                            << ssr << ";"
                            << x3 + x4 << ";" 
                            << x1 + x3 << ";" 
                            << y3 + y4 << ";" 
                            << y1 + y3 << ";" << endl;
                        break;
                    }
                    else
                    {
                        y1 = ytp1;
                        y2 = ytp2;
                        y3 = ytp3;
                        y4 = ytp4;
                        y5 = ytp5;
                        x1 = xtp1;
                        x2 = xtp2;
                        x3 = xtp3;
                        x4 = xtp4;
                    }
                }
                    // no convergence, odd.
                if (t==maxt)
                {
                        // calculate frequency Af
                        pe = x1 + x3;
                        qe = x3 + x4;
                        ps = y1 + y3;
                        qs = y3 + y4;

                        Dz = x1 * y4 + x4 * y1 - x2 * y3 - x3 * y2;
                        Demax = pe * (1.0 - qe) < (1.0 - pe) * qe ? pe * (1.0 - qe) : (1.0 - pe) * qe;
                        Dsmax = ps * (1.0 - qs) < (1.0 - ps) * qs ? ps * (1.0 - qs) : (1.0 - ps) * qs;
                        Dzprime = Dz == 0 ? 0 : Dz / (.5 * (Demax + Dsmax));

                        DataFile << "invade;" 
                            << t << ";" 
                            << tf << ";" 
                            << tm << ";" 
                            << h << ";" 
                            << cf << ";" 
                            << cm << ";" 
                            << kdrive << ";" 
                            << r << ";"
                            << Dz << ";"
                            << Demax << ";"
                            << Dsmax << ";"
                            << Dzprime << ";"
                            << y1 << ";" 
                            << y2 << ";" 
                            << y3 << ";" 
                            << y4 << ";" 
                            << y5 << ";"
                            << x1 << ";" 
                            << x2 << ";" 
                            << x3 << ";" 
                            << x4 << ";" 
                            << psr << ";" 
                            << ssr << ";"
                            << x3 + x4 << ";" 
                            << x1 + x3 << ";" 
                            << y3 + y4 << ";" 
                            << y1 + y3 << ";" << endl;
                }
            }
        }
    }
}
