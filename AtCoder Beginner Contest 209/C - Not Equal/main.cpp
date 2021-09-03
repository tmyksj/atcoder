#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    sort(c.begin(), c.end());

    long long mod = 1000000007;
    long long res = 1;

    for (int i = 0; i < n; i++) {
        res *= max(c[i] - i, 0);
        res %= mod;
    }

    cout << res << endl;
}
