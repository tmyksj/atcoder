#include <iostream>

using namespace std;

int main() {
    long long x;
    cin >> x;
    cout << (x - 1) / 11 * 2 + ((x - 1) % 11 + 1 <= 6 ? 1 : 2) << endl;
}
