#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<tuple<int, int>> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = make_tuple(a[i], i);
    }

    sort(b.begin(), b.end());

    vector<long long> res(n);
    for (int i = 0; i < n; i++) {
        res[get<1>(b[i])] = k / n + (i < k % n ? 1 : 0);
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << endl;
    }
}
