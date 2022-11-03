#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    int res = -1;

    for (int i = 0; i < 30; i++) {
        long long x = 1;

        for (int j = 0; j < 30; j++) {
            x *= 3;
            if (i == j) {
                x++;
            }
        }

        if (x == n) {
            res = i + 1;
        }
    }

    cout << res << endl;
}
