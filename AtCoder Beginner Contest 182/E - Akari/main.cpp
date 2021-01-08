#include <iostream>
#include <vector>

using namespace std;

int main() {
    int h, w, n, m;
    cin >> h >> w >> n >> m;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> c(m), d(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i] >> d[i];
    }

    vector<vector<int>> p(h + 2, vector<int>(w + 2, 0)),
            q(h + 2, vector<int>(w + 2, 0)),
            r(h + 2, vector<int>(w + 2, 0)),
            s(h + 2, vector<int>(w + 2, 0));

    for (int i = 0; i < h + 2; i++) {
        p[i][0] = p[i][w + 1] = -1;
        q[i][0] = q[i][w + 1] = -1;
        r[i][0] = r[i][w + 1] = -1;
        s[i][0] = s[i][w + 1] = -1;
    }

    for (int i = 0; i < w + 2; i++) {
        p[0][i] = p[h + 1][i] = -1;
        q[0][i] = q[h + 1][i] = -1;
        r[0][i] = r[h + 1][i] = -1;
        s[0][i] = s[h + 1][i] = -1;
    }

    for (int i = 0; i < n; i++) {
        p[a[i]][b[i]] = 1;
        q[a[i]][b[i]] = 1;
        r[a[i]][b[i]] = 1;
        s[a[i]][b[i]] = 1;
    }

    for (int i = 0; i < m; i++) {
        p[c[i]][d[i]] = -1;
        q[c[i]][d[i]] = -1;
        r[c[i]][d[i]] = -1;
        s[c[i]][d[i]] = -1;
    }

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if ((p[i][j] == 1 || p[i][j] == 2) && p[i][j + 1] == 0) {
                p[i][j + 1] = 2;
            }
        }
    }

    for (int i = 1; i <= h; i++) {
        for (int j = w; j >= 1; j--) {
            if ((q[i][j] == 1 || q[i][j] == 2) && q[i][j - 1] == 0) {
                q[i][j - 1] = 2;
            }
        }
    }

    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            if ((r[j][i] == 1 || r[j][i] == 2) && r[j + 1][i] == 0) {
                r[j + 1][i] = 2;
            }
        }
    }

    for (int i = 1; i <= w; i++) {
        for (int j = h; j >= 1; j--) {
            if ((s[j][i] == 1 || s[j][i] == 2) && s[j - 1][i] == 0) {
                s[j - 1][i] = 2;
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (p[i][j] > 0 || q[i][j] > 0 || r[i][j] > 0 || s[i][j] > 0) {
                res++;
            }
        }
    }

    cout << res << endl;
}
