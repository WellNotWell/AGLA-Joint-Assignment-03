#include <iostream>

using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif

int main() {

#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif

    double V0 = 40;
    double K0 = 40;
    double alpha1 = 0.34;
    double beta1 = 0.008;
    double alpha2 = 0.24;
    double beta2 = 0.004;
    double T = 100;

    fprintf(pipe, "set yrange [0:100]\n");
    fprintf(pipe, "set xrange [0:%lf]\n", T);

    fprintf(pipe, "set multiplot\n");
    fprintf(pipe, "set xlabel 'Time'\n");
    fprintf(pipe, "set ylabel 'Number of animals'\n");


    fprintf(pipe, "plot (%lf - %lf/%lf) * cos(sqrt(%lf * %lf) * x) - (%lf - %lf/%lf) * sqrt(%lf/%lf) * "
                  "%lf/%lf * sin(sqrt(%lf * %lf) * x) + (%lf/%lf) lc 'blue' linewidth 2 title 'Victims'\n", V0, alpha2,
                  beta2, alpha1, alpha2, K0, alpha1, beta1, alpha2, alpha1, beta1, beta2, alpha1, alpha2, alpha2, beta2);

    fprintf(pipe, "set key spacing 2.5\n");

    fprintf(pipe, "plot (%lf - %lf/%lf) * sqrt(%lf/%lf) * %lf/%lf * sin(sqrt(%lf * %lf) * x) + "
                  "(%lf - %lf/%lf) * cos(sqrt(%lf * %lf) * x) + (%lf/%lf) lc 'red' linewidth 2 title 'Killers'\n", V0,
                  alpha2, beta2, alpha1, alpha2, beta2, beta1, alpha1, alpha2, K0, alpha1, beta1, alpha1, alpha2,
                  alpha1, beta1);
    fflush(pipe);

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    return 0;
}
