#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<tuple<long long, long long>> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = make_tuple(a[i], b[i]);
    }

    sort(c.begin(), c.end());

    long long res = 0;
    for (long long i = 0, j = k; ; i++) {
        if (i == n || get<0>(c[i]) - res > j) {
            res += j;
            break;
        }

        j += get<1>(c[i]) - get<0>(c[i]) + res;
        res = get<0>(c[i]);
    }

    cout << res << endl;
}
