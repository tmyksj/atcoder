#include <iostream>

using namespace std;

int main() {
    long long n, d;
    cin >> n >> d;

    int res = 0;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        if (x * x + y * y <= d * d) {
            res++;
        }
    }

    cout << res << endl;
}
