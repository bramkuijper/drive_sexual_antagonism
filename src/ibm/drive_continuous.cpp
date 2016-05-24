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

// random number generator 
// see http://www.gnu.org/software/gsl/manual/html_node/Random-Number-Generation.html#Random-Number-Generation 
gsl_rng_type const * T; // gnu scientific library rng type
gsl_rng *r; // gnu scientific rng 

const size_t N = 10000;
const size_t numgen = 10000;
const size_t Clutch = 4;

size_t Nm = 0;
size_t Nf = 0;
size_t Nmjuv = 0;
size_t Nfjuv = 0;

// mutation rates
double mu = 0;
double sdmu = 0;
double mu_drive = 0;
double theta_f = 0;
double theta_m = 0;
double sd_f = 0;
double sd_m = 0;
double k = 0;
double cdm = 0;
double cdf = 0;
double h = 0;
double R = 0;

// runtime for stats
time_t total_time; 

size_t generation = 0;

int seed = -1;

// skip the number of generations in output
// to prevent output files from becoming too large
size_t skip = 10;

// different loci on the X
enum Xloc {
    X = 0,
    Xd= 1,
    Y = 2
};

// haploid individual
struct Individual
{
    Xloc drive_locus[2];
    double sa_locus[2];

    bool is_female;

    double v;
};


// generate the complete population
Individual Males[N];
Individual Females[N];
Individual Males2[N*Clutch];
Individual Females2[N*Clutch];

// give the outputfile a unique name based on a timestamp
// involving nanoseconds
// by using the create_filename function (see 
// "bramauxiliary.h")
string filename("sim_drive");
string filename_new(create_filename(filename));
ofstream DataFile(filename_new.c_str());  // output file 

// initialize the command line arguments to vary 
// the parameters
void init_arguments(int argc, char *argv[])
{
    mu  = atof(argv[1]);
    sdmu  = atof(argv[2]);
    mu_drive = atof(argv[3]);
    theta_f  = atof(argv[4]);
    theta_m  = atof(argv[5]);
    sd_f  = atof(argv[6]);
    sd_m  = atof(argv[7]);
    k  = atof(argv[8]);
    cdm  = atof(argv[9]);
    cdf  = atof(argv[10]);
    h  = atof(argv[11]);
    R  = atof(argv[12]);
}

void init_pop()
{
    // start the time
    total_time = time(NULL);

    // obtain a seed from current nanosecond count
	seed = get_nanoseconds();

    // set up the random number generators
    // (from the gnu gsl library)
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    gsl_rng_set(r, seed);

    // go through all individuals
    for (size_t i = 0; i < N/2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            Females[i].sa_locus[j] = 0;
            Females[i].drive_locus[j] = gsl_rng_uniform(r) < 0.5 ? X : Xd;
        }
    }
    
    for (size_t i = 0; i < N/2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            Males[i].sa_locus[j] = 0;
        }
            
        Males[i].drive_locus[0] = gsl_rng_uniform(r) < 0.5 ? X : Xd;
        Males[i].drive_locus[1] = Y;
    }

    Nf = N/2;
    Nm = N/2;
}

// mutate alleles
void Mut(Xloc &allele)
{
    if (gsl_rng_uniform(r) < mu_drive)
    {
        Xloc allele_new;
        do 
        {
            allele_new = (Xloc) gsl_rng_uniform_int(r, 3);
        } 
        while (allele_new == allele);

        allele = allele_new;
    }
}

void MutS(double &allele)
{
    if (gsl_rng_uniform(r) > mu)
    {
        return;
    }

    allele += gsl_ran_gaussian(r, sdmu);
}


// allocate a kid and give it genes
void create_kid(size_t mother, size_t father, Individual &Kid)
{
    size_t Xd_count = 0;
    size_t allele_from_mom = gsl_rng_uniform_int(r, 2);
    Kid.drive_locus[0] = Females[mother].drive_locus[allele_from_mom];

    Mut(Kid.drive_locus[0]);

    Xd_count += Kid.drive_locus[0] == Xd;


    allele_from_mom = gsl_rng_uniform(r) < 1.0 - R ? allele_from_mom : abs(allele_from_mom - 1);
    Kid.sa_locus[0] = Females[mother].sa_locus[allele_from_mom];
    MutS(Kid.sa_locus[0]);


    if (Males[father].drive_locus[0] == Xd)
    {
        if (gsl_rng_uniform(r) < k)
        {
            Kid.drive_locus[1] = Males[father].drive_locus[0];
            ++Xd_count;
        }
        else
        {
            Kid.drive_locus[1] = Males[father].drive_locus[1];
        }
    }
    else
    {
        Kid.drive_locus[1] = Males[father].drive_locus[gsl_rng_uniform_int(r, 2)];
    }

    Mut(Kid.drive_locus[1]);
    
    Kid.sa_locus[1] = Males[father].sa_locus[0];
    MutS(Kid.sa_locus[1]);

    // check whether current kid is female
    Kid.is_female = Kid.drive_locus[1] != Y;

    double opt = theta_m;
    double drive_cost = Xd_count > 0 ? cdm : 0;
    double sd = sd_m;

    if (Kid.is_female)
    {
        opt = theta_f;
        drive_cost = Xd_count > 1 ? cdf : (Xd_count > 0 ? h * cdf : 0);
        sd = sd_f;
    }

    Kid.v = exp(-.5 * pow((Kid.sa_locus[0] + Kid.sa_locus[1] - opt)/sd,2.0))*(1.0 - drive_cost);
}

void write_parameters()
{
    DataFile << endl << endl
            << "mu;" << mu << endl
            << "sdmu;" << sdmu << endl
            << "mu_drive;" << mu_drive << endl
            << "theta_f;" << theta_f << endl
            << "theta_m;" << theta_m << endl
            << "sd_f;" << sd_f << endl
            << "sd_m;" << sd_m << endl
            << "k;" << k << endl
            << "cdm;" << cdm << endl
            << "cdf;" << cdf << endl
            << "h;" << h << endl
            << "r;" << R << endl
            << "seed;" << seed << endl            
            << "runtime;" << total_time << endl;
}

void survive()
{
    if (Nm < 1 || Nf < 1)
    {
        cout << "extinct after reproduction" << endl;
        write_parameters();
        exit(0);
    }

    // payoff dependent survival
    for (size_t female_i = 0; female_i < Nf; ++female_i)
    {
        if (gsl_rng_uniform(r) > Females[female_i].v)
        {
            Females[female_i] = Females[Nf - 1];
            --Nf;
            --female_i;
        }
    }
    
    // payoff dependent survival
    for (size_t male_i = 0; male_i < Nm; ++ male_i)
    {
        if (gsl_rng_uniform(r) > Males[male_i].v)
        {
            Males[male_i] = Males[Nm - 1];
            --Nm;
            --male_i;
        }
    }
}



int reproduce()
{
    size_t random_male = 0;

    if (Nm < 1 || Nf < 1)
    {
        cout << "extinct after survival" << endl;
        write_parameters();
        exit(0);
    }

    Nfjuv = 0;
    Nmjuv = 0;


    for (size_t female_i = 0; female_i < Nf; ++female_i)
    {
        // find a mate
        random_male = gsl_rng_uniform_int(r, Nm);

        // create_kids
        for (size_t egg_i = 0; egg_i < Clutch; ++egg_i)
        {
            Individual Kid;

            create_kid(female_i, random_male, Kid);

            if (Kid.is_female)
            {
                Females2[Nfjuv++] = Kid;
            } 
            else
            {
                Males2[Nmjuv++] = Kid;
            }
        }
    }

    size_t rand_ind;

//    if (Nf > Nfjuv)
//    {
//        Nf = Nfjuv;
//    }
//    else if (Nfjuv > Nf && Nfjuv < N/2)
//    {
//        Nf = Nfjuv;
//    }
//    
//    if (Nm > Nmjuv)
//    {
//        Nm = Nmjuv;
//    }
//    else if (Nmjuv > Nm && Nmjuv < N/2)
//    {
//        Nm = Nmjuv;
//    }

    for (size_t female_i = 0; female_i < N/2; ++female_i)
    {
        assert(Nfjuv > 0);
        rand_ind = gsl_rng_uniform_int(r, Nfjuv);
        Females[female_i] = Females2[rand_ind];
//        Females2[rand_ind] = Females2[--Nfjuv];
    }
    
    for (size_t male_i = 0; male_i < N/2; ++male_i)
    {
        assert(Nmjuv > 0);
        rand_ind = gsl_rng_uniform_int(r, Nmjuv);
        Males[male_i] = Males2[rand_ind];
//        Males2[rand_ind] = Males2[--Nmjuv];
    }

    Nm = N/2;
    Nf = N/2;
    return(0);
}

void write_data_headers()
{
    DataFile << "generation;meanz;varz;pXd;pY;Nf;Nm;" << endl;
}

void write_data()
{
    double meanz = 0;
    double ssz = 0;

    double pY = 0;
    double pXd = 0;

    double z;

    for (size_t female_i = 0; female_i < Nf; ++female_i)
    {
        pXd += Females[female_i].drive_locus[0] == Xd;
        pXd += Females[female_i].drive_locus[1] == Xd;

        z = Females[female_i].sa_locus[0] + Females[female_i].sa_locus[1];

        meanz += z;
        ssz += z * z;
    }
    
    for (size_t male_i = 0; male_i < Nm; ++male_i)
    {
        pXd += Males[male_i].drive_locus[0] == Xd;
        pY += Males[male_i].drive_locus[1] == Y;

        z = Males[male_i].sa_locus[0]; 

        meanz += z;
        ssz += z * z;
    }

    meanz /= 2 * Nf + Nm;
    double varz = ssz / (2 * Nf + Nm) - meanz * meanz; 
    pXd /= 2 * Nf + Nm;
    pY /= 2*Nm;

    DataFile << generation << ";" << meanz << ";" << varz << ";" << pXd << ";" << pY << ";" << Nfjuv << ";" << Nmjuv << ";" << endl;
}



int main(int argc, char * argv[])
{
    init_arguments(argc,argv);
    init_pop();

    write_data_headers();

    for (generation = 0; generation < numgen; ++generation)
    {
        reproduce();
        if (generation % skip == 0)
        {
            write_data();
        }

        survive();
    }

    write_data();
    write_parameters();
}
