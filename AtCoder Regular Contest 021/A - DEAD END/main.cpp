#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> a(4, vector<int>(4));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a[i][j];
        }
    }

    bool res = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            res = res || a[i][j] == a[i][j + 1] || a[j][i] == a[j + 1][i];
        }
    }

    cout << (res ? "CONTINUE" : "GAMEOVER") << endl;
}
