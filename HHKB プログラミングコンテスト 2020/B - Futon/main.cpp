#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    int res = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i < h - 1 && s[i][j] == '.' && s[i + 1][j] == '.') {
                res++;
            }
            if (j < w - 1 && s[i][j] == '.' && s[i][j + 1] == '.') {
                res++;
            }
        }
    }

    cout << res << endl;
}
