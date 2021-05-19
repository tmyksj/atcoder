#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> a(h);
    for (int i = 0; i < h; i++) {
        cin >> a[i];
    }

    vector<vector<int>> b(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            b[i][j] = (a[i][j] == '+' ? 1 : -1);
        }
    }

    vector<vector<int>> c(h, vector<int>(w, 0));
    for (int i = h - 1; i >= 0; i--) {
        for (int j = w - 1; j >= 0; j--) {
            if ((i + j) % 2 == 0) {
                if (i + 1 < h && j + 1 < w) {
                    c[i][j] = max(c[i + 1][j] + b[i + 1][j], c[i][j + 1] + b[i][j + 1]);
                } else if (i + 1 < h) {
                    c[i][j] = c[i + 1][j] + b[i + 1][j];
                } else if (j + 1 < w) {
                    c[i][j] = c[i][j + 1] + b[i][j + 1];
                }
            } else {
                if (i + 1 < h && j + 1 < w) {
                    c[i][j] = min(c[i + 1][j] - b[i + 1][j], c[i][j + 1] - b[i][j + 1]);
                } else if (i + 1 < h) {
                    c[i][j] = c[i + 1][j] - b[i + 1][j];
                } else if (j + 1 < w) {
                    c[i][j] = c[i][j + 1] - b[i][j + 1];
                }
            }
        }
    }

    if (c[0][0] < 0) {
        cout << "Aoki" << endl;
    } else if (c[0][0] == 0) {
        cout << "Draw" << endl;
    } else {
        cout << "Takahashi" << endl;
    }
}
