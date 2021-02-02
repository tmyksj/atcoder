#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<long long> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = 2 * a[i] + b[i];
    }

    sort(c.begin(), c.end(), greater<long long>());

    for (int i = 1; i < n; i++) {
        c[i] += c[i - 1];
    }

    cout << distance(c.begin(), upper_bound(c.begin(), c.end(), accumulate(a.begin(), a.end(), 0LL))) + 1 << endl;
}
