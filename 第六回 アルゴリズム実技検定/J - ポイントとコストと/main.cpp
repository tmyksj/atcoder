#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    double c;
    cin >> n >> c;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    double p = accumulate(x.begin(), x.end(), 0.0) / n;

    double res = 0;
    for (int i = 0; i < n; i++) {
        res += (p - x[i]) * (p - x[i]) + (c - y[i]) * (c - y[i]);
    }

    cout << setprecision(12) << fixed << res << endl;
}
