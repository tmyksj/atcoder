#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string c;
    cin >> n >> c;

    string b = "ABXY";

    int res = n;
    for (int l = 0; l < 16; l++) {
        for (int r = 0; r < 16; r++) {
            int a = n;
            for (int i = 0; i < n - 1; i++) {
                if ((c[i] == b[l & 3] && c[i + 1] == b[l >> 2])
                        || (c[i] == b[r & 3] && c[i + 1] == b[r >> 2])) {
                    a--;
                    i++;
                }
            }

            res = min(res, a);
        }
    }

    cout << res << endl;
}
