#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dfs(int n, int m, vector<vector<int>>& g, vector<vector<int>>& h, int y, int x) {
    h[y][x] = 1;

    int dy[] = { -1, 0, 0, 1 };
    int dx[] = { 0, -1, 1, 0 };

    int r = 1;
    for (int i = 0; i < 4; i++) {
        if (g[y + dy[i]][x + dx[i]] == 0 && h[y + dy[i]][x + dx[i]] == 0) {
            r += dfs(n, m, g, h, y + dy[i], x + dx[i]);
        }
    }

    return r;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int w = n * m;
    vector<vector<int>> g(n + 2, vector<int>(m + 2, 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.') {
                w--;
                g[i + 1][j + 1] = 0;
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 1) {
                g[i][j] = 0;

                vector<vector<int>> h(n + 2, vector<int>(m + 2, 0));
                if (w + dfs(n, m, g, h, i, j) - 1 == n * m) {
                    res++;
                }

                g[i][j] = 1;
            }
        }
    }

    cout << res << endl;
}
