#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int x, y;
    string w;
    cin >> x >> y >> w;

    vector<string> c(9);
    for (int i = 0; i < 9; i++) {
        cin >> c[i];
    }

    for (int i = 0, j = y - 1, k = x - 1,
            dy = (w == "U" || w == "RU" || w == "LU" ? -1 : (w == "R" || w == "L" ? 0 : 1)),
            dx = (w == "L" || w == "LU" || w == "LD" ? -1 : (w == "U" || w == "D" ? 0 : 1));
            i < 4; i++, j += dy, k += dx) {
        cout << c[j][k];

        if (j + dy == -1 || j + dy == 9) {
            dy = -dy;
        }

        if (k + dx == -1 || k + dx == 9) {
            dx = -dx;
        }
    }

    cout << endl;
}
