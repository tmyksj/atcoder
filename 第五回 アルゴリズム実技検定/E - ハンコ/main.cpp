#include <algorithm>
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

    vector<string> t(h);
    for (int i = 0; i < h; i++) {
        cin >> t[i];
    }

    bool res = false;
    for (int i = 1 - max(h, w); i < max(h, w); i++) {
        for (int j = 1 - max(h, w); j < max(h, w); j++) {
            bool r0 = true, r1 = true, r2 = true, r3 = true;
            for (int k = 0; k < h; k++) {
                for (int l = 0; l < w; l++) {
                    if (t[k][l] == '.') {
                        continue;
                    }
                    if (i + k < 0 || h <= i + k
                            || j + l < 0 || w <= j + l
                            || s[i + k][j + l] == '#') {
                        r0 = false;
                    }
                    if (i + l < 0 || h <= i + l
                            || j + w - k - 1 < 0 || w <= j + w - k - 1
                            || s[i + l][j + w - k - 1] == '#') {
                        r1 = false;
                    }
                    if (i + h - k - 1 < 0 || h <= i + h - k - 1
                            || j + w - l - 1 < 0 || w <= j + w - l - 1
                            || s[i + h - k - 1][j + w - l - 1] == '#') {
                        r2 = false;
                    }
                    if (i + h - l - 1 < 0 || h <= i + h - l - 1
                            || j + k < 0 || w <= j + k
                            || s[i + h - l - 1][j + k] == '#') {
                        r3 = false;
                    }
                }
            }

            res = res || r0 || r1 || r2 || r3;
        }
    }

    cout << (res ? "Yes" : "No") << endl;
}
