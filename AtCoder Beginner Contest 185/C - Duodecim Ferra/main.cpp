#include <iostream>

using namespace std;

int main() {
    long long l;
    cin >> l;

    long long res = 1;
    for (long long i = l - 1; i > l - 12; i--) {
        res = res * i / (l - i);
    }

    cout << res << endl;
}
