#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    vector<long long> w(m);
    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }

    sort(h.begin(), h.end());

    vector<long long> p(n / 2 + 1, 0);
    for (int i = 0; i < n - 1; i += 2) {
        p[i / 2 + 1] = h[i + 1] - h[i];
        p[i / 2 + 1] += p[i / 2];
    }

    vector<long long> q(n / 2 + 1, 0);
    for (int i = 0; i < n - 1; i += 2) {
        q[i / 2 + 1] = h[n - i - 1] - h[n - i - 2];
        q[i / 2 + 1] += q[i / 2];
    }

    vector<long long> res(m);
    for (int i = 0; i < m; i++) {
        int j = distance(h.begin(), lower_bound(h.begin(), h.end(), w[i]));
        res[i] = p[j / 2] + q[n / 2 - j / 2] + (j % 2 == 0 ? h[j] - w[i] : w[i] - h[j - 1]);
    }

    cout << *min_element(res.begin(), res.end()) << endl;
}
