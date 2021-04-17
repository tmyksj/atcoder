#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    long long b, c;
    cin >> b >> c;

    if (b < 0) {
        cout << c / 2
                + 1
                + min(-b - 1, (c - 2) / 2)
                + min(-b, (c - 1) / 2)
                + 1
                + (c - 1) / 2 << endl;
    } else if (b == 0) {
        cout << c / 2
                + 1
                + (c - 1) / 2 << endl;
    } else {
        cout << (c - 1) / 2
                + 1
                + min(b - 1, (c - 1) / 2)
                + min(b, c / 2)
                + 1
                + (c - 2) / 2 << endl;
    }
}
