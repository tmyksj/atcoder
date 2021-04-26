#include <iostream>

using namespace std;

int main() {
    int x, y;
    cin >> x >> y;

    if (y == 0) {
        cout << "ERROR" << endl;
    } else {
        cout << x / y << "." << (100 * x / y) / 10 % 10 << (100 * x / y) % 10 << endl;
    }
}
