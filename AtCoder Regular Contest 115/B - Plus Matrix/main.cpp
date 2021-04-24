#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<int>> c(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }

    vector<int> a(n, 0), b(n, c[0][0]);
    for (int i = 1; i < n; i++) {
        a[i] = c[i][0] - c[0][0];
        b[i] = c[0][i];
    }

    for (int i = 0, j = *min_element(a.begin(), a.end()); i < n; i++) {
        a[i] -= j;
        b[i] += j;
    }

    bool res = true;
    for (int i = 0; i < n; i++) {
        res = res && a[i] >= 0 && b[i] >= 0;
        for (int j = 0; j < n; j++) {
            res = res && a[i] + b[j] == c[i][j];
        }
    }

    if (res) {
        cout << "Yes" << endl;

        for (int i = 0; i < n; i++) {
            cout << (i == 0 ? "" : " ") << a[i];
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << (i == 0 ? "" : " ") << b[i];
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }
}
