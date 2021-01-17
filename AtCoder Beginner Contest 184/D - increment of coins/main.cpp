#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 100;

    int a, b, c;
    cin >> a >> b >> c;

    vector<vector<vector<double>>> p(n + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, 0)));
    p[a][b][c] = 1;

    vector<vector<int>> q(3 * n, vector<int>(0)),
            r(3 * n, vector<int>(0)),
            s(3 * n, vector<int>(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                q[i + j + k].push_back(i);
                r[i + j + k].push_back(j);
                s[i + j + k].push_back(k);
            }
        }
    }

    for (int i = 1; i < 3 * n; i++) {
        for (int j = 0; j < static_cast<int>(q[i].size()); j++) {
            int qij = q[i][j], rij = r[i][j], sij = s[i][j];
            p[qij + 1][rij][sij] += p[qij][rij][sij] * qij / (qij + rij + sij);
            p[qij][rij + 1][sij] += p[qij][rij][sij] * rij / (qij + rij + sij);
            p[qij][rij][sij + 1] += p[qij][rij][sij] * sij / (qij + rij + sij);
        }
    }

    double res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res += p[n][i][j] * (n + i + j - a - b - c);
            res += p[i][n][j] * (i + n + j - a - b - c);
            res += p[i][j][n] * (i + j + n - a - b - c);
        }
    }

    cout << setprecision(12) << fixed << res << endl;
}
