#include <iostream>

using namespace std;

int main() {
    int a, b, x;
    cin >> a >> b >> x;
    cout << (a <= x && x <= a + b ? "YES" : "NO") << endl;
}
