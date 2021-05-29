#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dfs(int h, int w, vector<string>& s, int i, int j, vector<vector<int>>& res) {
    int op[] = { 'v', '>', '<', '^' };
    int dy[] = { -1, 0, 0, 1 };
    int dx[] = { 0, -1, 1, 0 };

    res[i][j] = 'o';
    for (int k = 0; k < 4; k++) {
        if (0 <= i + dy[k] && i + dy[k] < h
                && 0 <= j + dx[k] && j + dx[k] < w
                && (s[i + dy[k]][j + dx[k]] == '.'
                        || s[i + dy[k]][j + dx[k]] == op[k])
                && res[i + dy[k]][j + dx[k]] == 'x') {
            dfs(h, w, s, i + dy[k], j + dx[k], res);
        }
    }
}

int main() {
    int h, w, r, c;
    cin >> h >> w >> r >> c;

    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    vector<vector<int>> res(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            res[i][j] = (s[i][j] == '#' ? '#' : 'x');
        }
    }

    dfs(h, w, s, r - 1, c - 1, res);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << static_cast<char>(res[i][j]);
        }
        cout << endl;
    }
}
