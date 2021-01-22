#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (int i = 0; i < h; i++) {
        cin >> a[i];
    }

    int sy, sx, gy, gx;
    vector<vector<int>> b(h + 2, vector<int>(w + 2, -1));
    map<int, vector<tuple<int, int>>> m;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (a[i - 1][j - 1] == 'S') {
                sy = i;
                sx = j;
                b[i][j] = 0;
            } else if (a[i - 1][j - 1] == 'G') {
                gy = i;
                gx = j;
                b[i][j] = 0;
            } else if (a[i - 1][j - 1] == '.') {
                b[i][j] = 0;
            } else if (a[i - 1][j - 1] != '#') {
                b[i][j] = a[i - 1][j - 1];
                m[b[i][j]].push_back(make_tuple(i, j));
            }
        }
    }

    int inf = 1 << 29;
    int dy[] = { -1, 0, 0, 1 };
    int dx[] = { 0, -1, 1, 0 };

    vector<vector<int>> d(h + 2, vector<int>(w + 2, inf));
    d[sy][sx] = 0;

    priority_queue<tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>> que;
    que.push(make_tuple(0, sy, sx));

    while (!que.empty()) {
        tuple<int, int, int> q = que.top();
        que.pop();

        int y = get<1>(q);
        int x = get<2>(q);

        if (b[y][x] >= 0) {
            for (int i = 0; i < 4; i++) {
                if (b[y + dy[i]][x + dx[i]] >= 0 && d[y + dy[i]][x + dx[i]] > d[y][x] + 1) {
                    d[y + dy[i]][x + dx[i]] = d[y][x] + 1;
                    que.push(make_tuple(d[y + dy[i]][x + dx[i]], y + dy[i], x + dx[i]));
                }
            }
        }

        if (m.find(b[y][x]) != m.end()) {
            for (vector<tuple<int, int>>::iterator i = m[b[y][x]].begin(); i != m[b[y][x]].end(); i++) {
                if (d[get<0>(*i)][get<1>(*i)] > d[y][x] + 1) {
                    d[get<0>(*i)][get<1>(*i)] = d[y][x] + 1;
                    que.push(make_tuple(d[get<0>(*i)][get<1>(*i)], get<0>(*i), get<1>(*i)));
                }
            }

            m.erase(b[y][x]);
        }
    }

    if (d[gy][gx] < inf) {
        cout << d[gy][gx] << endl;
    } else {
        cout << "-1" << endl;
    }
}
