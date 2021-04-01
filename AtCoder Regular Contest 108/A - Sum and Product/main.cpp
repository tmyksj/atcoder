#include <iostream>

using namespace std;

int main() {
    long long s, p;
    cin >> s >> p;

    bool res = false;
    for (long long i = 1; i * i <= p; i++) {
        if (s - i == p / i && p % i == 0) {
            res = true;
            break;
        }
    }

    cout << (res ? "Yes" : "No") << endl;
}
