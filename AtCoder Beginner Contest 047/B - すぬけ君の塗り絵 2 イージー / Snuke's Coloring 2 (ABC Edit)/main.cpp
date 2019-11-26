#include <iostream>
#include <vector>

using namespace std;

int main() {
    int w, h, n;
    cin >> w >> h >> n;

    vector<vector<int>> grid(h, vector<int>(w, 1));
    for (int i = 0; i < n; i++) {
        int x, y, a;
        cin >> x >> y >> a;

        for (int j = (a == 4 ? y : 0); j < (a == 3 ? y : h); j++) {
            for (int k = (a == 2 ? x : 0); k < (a == 1 ? x : w); k++) {
                grid[j][k] = 0;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            res += grid[i][j];
        }
    }

    cout << res << endl;
}
