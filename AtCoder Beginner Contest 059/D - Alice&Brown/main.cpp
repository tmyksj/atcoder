#include <iostream>

using namespace std;

int main() {
    long long x, y;
    cin >> x >> y;
    cout << ((x > y ? x - y : y - x) > 1 ? "Alice" : "Brown") << endl;
}
