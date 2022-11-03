#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void solve(long long n, vector<long long>& a) {
    if (n == 0) {
        return;
    }

    long long m = abs(n);

    long long b = 1, c = 1;
    while (c < m) {
        b *= 3;
        c += b;
    }

    a.push_back(n > 0 ? b : -b);
    solve(n > 0 ? n - b : n + b, a);
}

int main() {
    long long n;
    cin >> n;

    vector<long long> a(0);
    solve(n, a);

    cout << a.size() << endl;
    for (int i = 0; i < static_cast<int>(a.size()); i++) {
        cout << (i == 0 ? "" : " ") << a[i];
    }
    cout << endl;
}
