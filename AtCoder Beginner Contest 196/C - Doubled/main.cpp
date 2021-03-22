#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long res = 0;
    for (long long i = 1, j = 10; i * (j + 1) <= n; i++, j *= (i == j ? 10 : 1)) {
        res++;
    }

    cout << res << endl;
}
