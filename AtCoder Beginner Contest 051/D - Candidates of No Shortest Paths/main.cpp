#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> c[i];
        a[i]--; b[i]--;
    }

    vector<vector<int>> dist(n, vector<int>(n, 1 << 29));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        dist[a[i]][b[i]] = c[i];
        dist[b[i]][a[i]] = c[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (dist[j][k] > dist[j][i] + dist[i][k]) {
                    dist[j][k] = dist[j][i] + dist[i][k];
                }
            }
        }
    }

    int res = m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[j][a[i]] + c[i] == dist[j][b[i]]) {
                res--;
                break;
            }
        }
    }

    cout << res << endl;
}
