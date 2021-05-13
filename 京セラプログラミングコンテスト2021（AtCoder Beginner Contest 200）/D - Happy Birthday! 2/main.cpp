#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int mod = 200;

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<long long>> s(mod, vector<long long>(0));
    for (int i = 1; i < (1 << min(n, 8)); i++) {
        long long t = 0;
        for (int j = 0; j < min(n, 8); j++) {
            if ((i & (1 << j)) > 0) {
                t += a[j];
            }
        }

        s[t % mod].push_back(i);
    }

    int b = -1, c = -1, x = 0, y = 0;
    for (int i = 0; i < mod; i++) {
        if (s[i].size() >= 2) {
            b = s[i][0];
            c = s[i][1];

            for (int j = b; j > 0; j /= 2) {
                x += j % 2;
            }
            for (int j = c; j > 0; j /= 2) {
                y += j % 2;
            }

            break;
        }
    }

    if (b > 0) {
        cout << "Yes" << endl;

        cout << x;
        for (int i = 0; i < min(n, 8); i++) {
            if ((b & (1 << i)) > 0) {
                cout << " " << i + 1;
            }
        }
        cout << endl;

        cout << y;
        for (int i = 0; i < min(n, 8); i++) {
            if ((c & (1 << i)) > 0) {
                cout << " " << i + 1;
            }
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }
}
