#include <algorithm>
#include <iostream>
#include <vector>
#include <vector>

using namespace std;

int main() {
    vector<int> f(12);
    f[0] = 0;
    f[1] = f[0] + 31;
    f[2] = f[1] + 29;
    f[3] = f[2] + 31;
    f[4] = f[3] + 30;
    f[5] = f[4] + 31;
    f[6] = f[5] + 30;
    f[7] = f[6] + 31;
    f[8] = f[7] + 31;
    f[9] = f[8] + 30;
    f[10] = f[9] + 31;
    f[11] = f[10] + 30;

    int n;
    cin >> n;

    vector<string> md(n);
    for (int i = 0; i < n; i++) {
        cin >> md[i];
    }

    vector<int> m(n), d(n);
    for (int i = 0; i < n; i++) {
        if (md[i][1] == '/') {
            m[i] = md[i][0] - '0';
            if (md[i].size() == 3) {
                d[i] = md[i][2] - '0';
            } else {
                d[i] = 10 * (md[i][2] - '0') + md[i][3] - '0';
            }
        } else {
            m[i] = 10 * (md[i][0] - '0') + md[i][1] - '0';
            if (md[i].size() == 4) {
                d[i] = md[i][3] - '0';
            } else {
                d[i] = 10 * (md[i][3] - '0') + md[i][4] - '0';
            }
        }
    }

    vector<int> h(366, 0);
    for (int i = 0; i < 366; i++) {
        if (i % 7 == 0 || i % 7 == 6) {
            h[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = f[m[i] - 1] + d[i] - 1; j < 366; j++) {
            if (h[j] == 0) {
                h[j] = 1;
                break;
            }
        }
    }

    int res = 0;
    for (int i = 0, j = 0; i < 366; i++) {
        if (h[i] == 0) {
            j = 0;
        } else {
            j++;
        }

        res = max(res, j);
    }

    cout << res << endl;
}
