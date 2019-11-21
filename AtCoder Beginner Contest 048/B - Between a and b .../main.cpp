#include <iostream>

using namespace std;

int main() {
    long long a, b, x;
    cin >> a >> b >> x;
    cout << b / x - (a + x - 1) / x + 1 << endl;
}
