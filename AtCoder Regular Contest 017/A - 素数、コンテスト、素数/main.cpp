#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    bool res = true;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = false;
        }
    }

    cout << (res ? "YES" : "NO") << endl;
}
