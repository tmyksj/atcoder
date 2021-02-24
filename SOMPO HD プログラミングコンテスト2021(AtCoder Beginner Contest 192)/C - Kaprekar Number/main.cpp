#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n;
    int k;
    cin >> n >> k;

    long long res = n;
    for (int i = 0; i < k; i++) {
        vector<int> v(0);
        for (long long j = res; j > 0; j /= 10) {
            v.push_back(j % 10);
        }

        sort(v.begin(), v.end());

        long long g1 = 0, g2 = 0;
        for (int j = 0; j < static_cast<int>(v.size()); j++) {
            g1 = 10 * g1 + v[v.size() - j - 1];
            g2 = 10 * g2 + v[j];
        }

        res = g1 - g2;
    }

    cout << res << endl;
}
