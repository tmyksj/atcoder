#include <iostream>
#include <vector>

using namespace std;

int solve(int h, int w, int a, int b, vector<vector<int>> t, int i, int j) {
    if (i > h) {
        return 1;
    }

    int res = 0;

    if (t[i][j] == 1) {
        res += solve(h, w, a, b, t, j < w ? i : i + 1, j < w ? j + 1 : 1);
    }

    if (b > 0 && t[i][j] == 0) {
        t[i][j] = 1;
        res += solve(h, w, a, b - 1, t, j < w ? i : i + 1, j < w ? j + 1 : 1);
        t[i][j] = 0;
    }

    if (a > 0 && j < w && t[i][j] == 0 && t[i][j + 1] == 0) {
        t[i][j] = t[i][j + 1] = 1;
        res += solve(h, w, a - 1, b, t, j < w ? i : i + 1, j < w ? j + 1 : 1);
        t[i][j] = t[i][j + 1] = 0;
    }

    if (a > 0 && i < h && t[i][j] == 0 && t[i + 1][j] == 0) {
        t[i][j] = t[i + 1][j] = 1;
        res += solve(h, w, a - 1, b, t, j < w ? i : i + 1, j < w ? j + 1 : 1);
        t[i][j] = t[i + 1][j] = 0;
    }

    return res;
}

int main() {
    int h, w, a, b;
    cin >> h >> w >> a >> b;

    vector<vector<int>> t(h + 2, vector<int>(w + 2, 1));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            t[i][j] = 0;
        }
    }

    cout << solve(h, w, a, b, t, 1, 1) << endl;
}
