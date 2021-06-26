#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long res = 0;
    while (res * (res + 1) / 2 < n) {
        res++;
    }

    cout << res << endl;
}
