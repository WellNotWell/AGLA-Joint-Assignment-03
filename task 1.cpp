#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

int main() {

    double V0, K0, alpha1, beta1, alpha2, beta2, T;
    int N;
    cin >> V0 >> K0 >> alpha1 >> beta1 >> alpha2 >> beta2 >> T >> N;

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

    cout << "t:" << endl;
    for (int i = 0; i <= N; i++) {
        cout << fixed << setprecision(2);
        cout << t[i] << " ";
    }
    cout << endl;

    cout << "v:" << endl;
    for (int i = 0; i <= N; i++) {
        cout << fixed << setprecision(2);
        cout << v[i] << " ";
    }
    cout << endl;

    cout << "k:" << endl;
    for (int i = 0; i <= N; i++) {
        cout << fixed << setprecision(2);
        cout << k[i] << " ";
    }
    cout << endl;

    return 0;
}
