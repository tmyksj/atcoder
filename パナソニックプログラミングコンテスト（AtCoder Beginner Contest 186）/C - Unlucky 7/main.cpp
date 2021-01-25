#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 1; i <= n; i++) {
        int r = 1;

        for (int j = i; j > 0; j /= 8) {
            if (j % 8 == 7) {
                r = 0;
            }
        }

        for (int j = i; j > 0; j /= 10) {
            if (j % 10 == 7) {
                r = 0;
            }
        }

        res += r;
    }

    cout << res << endl;
}
