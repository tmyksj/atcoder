#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    int inf = 1 << 29;

    vector<vector<int>> d(h, vector<int>(w, inf));
    d[0][0] = 0;

    priority_queue<tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>> que;
    que.push(make_tuple(0, 0, 0));
    while (!que.empty()) {
        tuple<int, int, int> q = que.top();
        que.pop();

        int y = get<1>(q);
        int x = get<2>(q);

        int dy0[] = { -1, 0, 0, 1 };
        int dx0[] = { 0, -1, 1, 0 };

        for (int i = 0; i < 4; i++) {
            if (0 <= y + dy0[i] && y + dy0[i] < h
                    && 0 <= x + dx0[i] && x + dx0[i] < w
                    && s[y + dy0[i]][x + dx0[i]] == '.'
                    && d[y + dy0[i]][x + dx0[i]] > d[y][x]) {
                d[y + dy0[i]][x + dx0[i]] = d[y][x];
                que.push(make_tuple(d[y + dy0[i]][x + dx0[i]], y + dy0[i], x + dx0[i]));
            }
        }

        int dy1[] = { -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2 };
        int dx1[] = { -1, 0, 1, -2, -1, 0, 1, 2, -2, -1, 1, 2, -2, -1, 0, 1, 2, -1, 0, 1 };

        for (int i = 0; i < 20; i++) {
            if (0 <= y + dy1[i] && y + dy1[i] < h
                    && 0 <= x + dx1[i] && x + dx1[i] < w
                    && d[y + dy1[i]][x + dx1[i]] > d[y][x] + 1) {
                d[y + dy1[i]][x + dx1[i]] = d[y][x] + 1;
                que.push(make_tuple(d[y + dy1[i]][x + dx1[i]], y + dy1[i], x + dx1[i]));
            }
        }
    }

    cout << d[h - 1][w - 1] << endl;
}
