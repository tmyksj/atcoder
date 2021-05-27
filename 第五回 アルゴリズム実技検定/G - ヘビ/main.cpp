#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

bool solve(int h, int w, vector<string>& s, int k, int i, int j,
        vector<vector<bool>>& p, vector<tuple<int, int>>& res) {
    p[i][j] = false;
    res.push_back(make_tuple(i, j));
    if (static_cast<int>(res.size()) == k) {
        return true;
    }

    bool ret = false;

    int dy[] = { -1, 0, 0, 1 };
    int dx[] = { 0, -1, 1, 0 };
    for (int l = 0; l < 4 && !ret; l++) {
        if (0 <= i + dy[l] && i + dy[l] < h
                && 0 <= j + dx[l] && j + dx[l] < w
                && s[i + dy[l]][j + dx[l]] == '#'
                && p[i + dy[l]][j + dx[l]]) {
            ret = solve(h, w, s, k, i + dy[l], j + dx[l], p, res);
        }
    }

    if (ret) {
        return true;
    } else {
        p[i][j] = true;
        res.pop_back();
        return false;
    }
}

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    int k = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                k++;
            }
        }
    }

    vector<tuple<int, int>> res(0);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            vector<vector<bool>> p(h, vector<bool>(w, true));
            if (s[i][j] == '#' && solve(h, w, s, k, i, j, p, res)) {
                goto out;
            }
        }
    }

out:
    cout << k << endl;
    for (int i = 0; i < static_cast<int>(res.size()); i++) {
        cout << get<0>(res[i]) + 1 << " " << get<1>(res[i]) + 1 << endl;
    }
}
