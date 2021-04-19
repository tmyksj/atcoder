#include <iostream>

using namespace std;

int main() {
    long long k;
    cin >> k;

    long long res = 0;
    for (long long a = 1; a <= k; a++) {
        for (long long b = 1; a * b <= k; b++) {
            res += k / (a * b);
        }
    }

    cout << res << endl;
}
