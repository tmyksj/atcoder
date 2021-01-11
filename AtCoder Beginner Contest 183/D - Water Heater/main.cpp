#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n, w;
    cin >> n >> w;

    vector<long long> s(n), t(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i] >> p[i];
    }

    vector<long long> q(*max_element(t.begin(), t.end()) + 1, 0);
    for (int i = 0; i < n; i++) {
        q[s[i]] += p[i];
        q[t[i]] -= p[i];
    }

    bool res = q[0] <= w;
    for (int i = 1; i < static_cast<int>(q.size()); i++) {
        q[i] += q[i - 1];
        res = res && q[i] <= w;
    }

    cout << (res ? "Yes" : "No") << endl;
}
