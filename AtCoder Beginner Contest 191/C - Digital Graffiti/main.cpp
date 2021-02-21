#include <iostream>
#include <map>
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
    for (int i = 0; i < h - 1; i++) {
        for (int j = 0; j < w - 1; j++) {
            map<int, int> m;
            m[s[i][j]]++;
            m[s[i][j + 1]]++;
            m[s[i + 1][j]]++;
            m[s[i + 1][j + 1]]++;

            if (m['#'] == 1 || m['#'] == 3) {
                res++;
            }
        }
    }

    cout << res << endl;
}
