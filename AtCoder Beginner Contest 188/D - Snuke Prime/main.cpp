#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    long long n, c;
    cin >> n >> c;

    vector<long long> ai(n), bi(n), ci(n);
    for (int i = 0; i < n; i++) {
        cin >> ai[i] >> bi[i] >> ci[i];
    }

    map<long long, long long> m;
    for (int i = 0; i < n; i++) {
        m[ai[i]] += ci[i];
        m[bi[i] + 1] -= ci[i];
    }

    vector<long long> d(0), s(0);
    for (map<long long, long long>::iterator i = m.begin(); i != m.end(); i++) {
        d.push_back(i->first);
        s.push_back(i->second);
    }

    for (int i = 1; i < static_cast<int>(d.size()); i++) {
        s[i] += s[i - 1];
    }

    long long res = 0;
    for (int i = 1; i < static_cast<int>(d.size()); i++) {
        res += (d[i] - d[i - 1]) * min(s[i - 1], c);
    }

    cout << res << endl;
}
