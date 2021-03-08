#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<long long, long long> m;
    for (int i = 0; i < n; i++) {
        m[a[i]]++;
    }

    long long res = 0;
    for (map<long long, long long>::iterator i = m.begin(); i != m.end(); i++) {
        for (map<long long, long long>::iterator j = i; j != m.end(); j++) {
            if (i == j) {
                res += (i->first - j->first) * (i->first - j->first) * i->second * (j->second - 1);
            } else {
                res += (i->first - j->first) * (i->first - j->first) * i->second * j->second;
            }
        }
    }

    cout << res << endl;
}
