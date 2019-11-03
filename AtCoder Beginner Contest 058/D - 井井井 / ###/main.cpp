#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<long long> y(m);
    for (int i = 0; i < m; i++) {
        cin >> y[i];
    }

    long long x_sum = 0;
    for (int i = 0; i < n; i++) {
        x_sum += i * x[i] - (n - i - 1) * x[i];
        x_sum %= 1000000007;
    }

    long long y_sum = 0;
    for (int i = 0; i < m; i++) {
        y_sum += i * y[i] - (m - i - 1) * y[i];
        y_sum %= 1000000007;
    }

    cout << x_sum * y_sum % 1000000007 << endl;
}
