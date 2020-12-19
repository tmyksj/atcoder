#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    int d = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d = max(d, (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
    }

    cout << setprecision(12) << fixed << sqrt(static_cast<double>(d)) << endl;
}
