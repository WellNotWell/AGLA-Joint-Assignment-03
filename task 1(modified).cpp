#include <iostream>
#include <cmath>
#include <vector>

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
    int N = 1000;

    double dt = T/N;
    vector<double> t(N+1), v(N+1), k(N+1);

    t[0] = 0;
    v[0] = V0;
    k[0] = K0;

    for (int i = 1; i <= N; i++) {
        t[i] = t[i-1] + dt;
        v[i] = (V0 - alpha2/beta2) * cos(sqrt(alpha1 * alpha2) * t[i]) - (K0 - alpha1/beta1) *
                sqrt(alpha2/alpha1) * beta1/beta2 * sin(sqrt(alpha1 * alpha2) * t[i]) + (alpha2/beta2);
        k[i] = (V0 - alpha2/beta2) * sqrt(alpha1/alpha2) * beta2/beta1 * sin(sqrt(alpha1 * alpha2) * t[i])
               + (K0 - alpha1/beta1) * cos(sqrt(alpha1 * alpha2) * t[i]) + (alpha1/beta1);
    }

    fprintf(pipe, "set yrange [0:100]\n");
    fprintf(pipe, "set xrange [0:%lf]\n", T);

    fprintf(pipe, "set multiplot\n");
    fprintf(pipe, "set xlabel 'Time'\n");
    fprintf(pipe, "set ylabel 'Number of animals'\n");

    fprintf(pipe, "plot '-' lc 'blue' linewidth 2 title 'Victims' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", t[i], v[i]);
    }

    fprintf(pipe, "e\n");
    fprintf(pipe, "set key spacing 2.5\n");

    fprintf(pipe, "plot '-' lc 'red' linewidth 2 title 'Killers' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", t[i], k[i]);
    }

    fprintf(pipe, "e\n");
    fprintf(pipe, "unset multiplot\n");
    fflush(pipe);

    fprintf(pipe, "set term wxt 1\n");

    fprintf(pipe, "set xlabel 'Number of victims'\n");
    fprintf(pipe, "set ylabel 'Number of killers'\n");

    fprintf(pipe, "plot '-' lc 'dark-red' linewidth 2 title 'Killers' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", v[i], k[i]);
    }

    fprintf(pipe, "e\n");

    fflush(pipe);

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    return 0;
}
