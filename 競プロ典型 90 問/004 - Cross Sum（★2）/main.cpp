#include <iostream>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> s(h, 0), t(w, 0);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            s[i] += a[i][j];
            t[j] += a[i][j];
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << (j == 0 ? "" : " ") << s[i] + t[j] - a[i][j];
        }
        cout << endl;
    }
}
