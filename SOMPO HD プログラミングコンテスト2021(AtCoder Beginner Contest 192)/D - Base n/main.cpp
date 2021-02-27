#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string x;
    long long m;
    cin >> x >> m;

    int n = x.size();

    if (n == 1) {
        cout << (x[0] - '0' <= m ? "1" : "0") << endl;
    } else {
        int d = *max_element(x.begin(), x.end()) - '0' + 1;

        long long l = d, r = m + 1;
        while (l < r) {
            long long c = (l + r + 1) / 2;

            bool overflow = false;
            for (long long i = 0, j = 1, k = 0; i < n; i++, j *= c) {
                k += (x[n - i - 1] - '0') * j;
                if (k > m || (i < n - 1 && j > (m + c - 1) / c)) {
                    overflow = true;
                }
            }

            if (overflow) {
                r = c - 1;
            } else {
                l = c;
            }
        }

        for (long long i = 0, j = 1, k = 0; i < n; i++, j *= l) {
            k += (x[n - i - 1] - '0') * j;
            if (k > m || (i < n - 1 && j > (m + l - 1) / l)) {
                l--;
                break;
            }
        }

        cout << l - d + 1 << endl;
    }
}
