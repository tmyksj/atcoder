#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    double res = 0;
    for (int i = 1; i < n; i++) {
        res += static_cast<double>(n) / i;
    }

    cout << setprecision(12) << fixed << res << endl;
}
