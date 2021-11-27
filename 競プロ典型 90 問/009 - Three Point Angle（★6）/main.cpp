#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    const double pi = 3.14159265358979323846264338327950288;

    int n;
    cin >> n;

    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    double res = 0;
    for (int i = 0; i < n; i++) {
        vector<double> d(0);

        for (int j = 0; j < n; j++) {
            if (i != j) {
                double a = atan2(y[j] - y[i], x[j] - x[i]) * 180.0 / pi;

                if (a <= 0) {
                    a += 360.0;
                }

                d.push_back(a);
                d.push_back(a + 360.0);
            }
        }

        sort(d.begin(), d.end());

        for (int j = 0; j < 2 * n - 3; j++) {
            int k = distance(d.begin(), lower_bound(d.begin() + j + 1, d.end(), d[j] + 180.0));

            if (k < 2 * n - 2) {
                res = max(res, min(d[k] - d[j], d[j] - d[k] + 360.0));
            }

            res = max(res, min(d[k - 1] - d[j], d[j] - d[k - 1] + 360.0));
        }
    }

    cout << setprecision(12) << fixed << res << endl;
}
