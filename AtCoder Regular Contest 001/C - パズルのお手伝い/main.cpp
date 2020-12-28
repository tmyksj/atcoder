#include <iostream>
#include <vector>

using namespace std;

bool solve(int n, vector<string>& c, int i, int r) {
    if (i == n) {
        return r == 0;
    }

    int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int j = 0; j < n; j++) {
        bool s = true;
        for (int k = 0; k < 8; k++) {
            for (int y = i + dy[k], x = j + dx[k];
                    0 <= y && y < n && 0 <= x && x < n;
                    y += dy[k], x += dx[k]) {
                if (c[y][x] == 'Q') {
                    s = false;
                }
            }
        }

        if (s && c[i][j] == 'Q') {
            if (solve(n, c, i + 1, r)) {
                return true;
            }
        } else if (s && c[i][j] == '.') {
            c[i][j] = 'Q';
            if (solve(n, c, i + 1, r - 1)) {
                return true;
            }
            c[i][j] = '.';
        }
    }

    return false;
}

int main() {
    int n = 8;

    vector<string> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    int r = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (c[i][j] == 'Q') {
                r--;
            }
        }
    }

    bool res = solve(n, c, 0, r);

    if (res) {
        for (int i = 0; i < n; i++) {
            cout << c[i] << endl;
        }
    } else {
        cout << "No Answer" << endl;
    }
}
