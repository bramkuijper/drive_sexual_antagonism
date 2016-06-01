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

    double bound = 1e-07;
    int maxt = 10000000;

    DataFile << "type;t;tf;tm;h;cf;cm;kdrive;r;y1;y2;y3;y4;y5;x1;x2;x3;x4;psr;ssr;fxd;faf;mxd;maf;" << endl;

    for (double tf = 0; tf <= 1.0; tf+=0.01)
    {
        for (double tm = 0; tm <= 1.0; tm+=0.01)
        {
            for (double h = 0; h <= 1.0; h+= 0.1)
            {
                x1 = 0;
                x2 = 0.5;
                x3 = 0;
                x4 = 0.5;
                
                y1 = 0;
                y2 = 0.25;
                y3 = 0;
                y4 = 0.25;
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
                        DataFile << "init;" << t << ";" << tf << ";" << tm << ";" << h << ";" << cf << ";" << cm << ";" << kdrive << ";" << r << ";";
                        DataFile << y1 << ";" << y2 << ";" << y3 << ";" << y4 << ";" << y5 << ";";
                        DataFile << x1 << ";" << x2 << ";" << x3 << ";" << x4 << ";" << psr << ";" << ssr << ";";
                        DataFile << x3 + x4 << ";" << x1 + x3 << ";" << y3 + y4 << ";" << y1 + y3 << ";" << endl;
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
                        DataFile << "init;" << t << ";" << tf << ";" << tm << ";" << h << ";" << cf << ";" << cm << ";" << kdrive << ";" << r << ";";
                        DataFile << y1 << ";" << y2 << ";" << y3 << ";" << y4 << ";" << y5 << ";";
                        DataFile << x1 << ";" << x2 << ";" << x3 << ";" << x4 << ";" << psr << ";" << ssr << ";";
                        DataFile << x3 + x4 << ";" << x1 + x3 << ";" << y3 + y4 << ";" << y1 + y3 << ";" << endl;
                }

                assert(x1 == 0);
                assert(x3 == 0);

                x1 = 0.000005; 
                x3 = 0.000005;
                
                y1 = 0.000005; 
                y3 = 0.000005;

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
                        DataFile << "invade;" << t << ";" << tf << ";" << tm << ";" << h << ";" << cf << ";" << cm << ";" << kdrive << ";" << r << ";";
                        DataFile << y1 << ";" << y2 << ";" << y3 << ";" << y4 << ";" << y5 << ";";
                        DataFile << x1 << ";" << x2 << ";" << x3 << ";" << x4 << ";" << psr << ";" << ssr << ";";
                        DataFile << x3 + x4 << ";" << x1 + x3 << ";" << y3 + y4 << ";" << y1 + y3 << ";" << endl;
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
                        DataFile << "invade;" << t << ";" << tf << ";" << tm << ";" << h << ";" << cf << ";" << cm << ";" << kdrive << ";" << r << ";";
                        DataFile << y1 << ";" << y2 << ";" << y3 << ";" << y4 << ";" << y5 << ";";
                        DataFile << x1 << ";" << x2 << ";" << x3 << ";" << x4 << ";" << psr << ";" << ssr << ";";
                        DataFile << x3 + x4 << ";" << x1 + x3 << ";" << y3 + y4 << ";" << y1 + y3 << ";" << endl;
                }
            }
        }
    }
}
