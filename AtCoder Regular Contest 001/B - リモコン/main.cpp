#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    int res = 1 << 29;
    for (int i = -4; i <= 4; i++) {
        for (int j = -8; j <= 8; j++) {
            res = min(res, abs(i) + abs(j) + abs(a + 10 * i + 5 * j - b));
        }
    }

    cout << res << endl;
}
